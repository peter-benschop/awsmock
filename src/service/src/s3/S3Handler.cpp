
#include <awsmock/service/S3Handler.h>

namespace AwsMock::Service {

  S3Handler::S3Handler(Core::Configuration &configuration, Core::MetricService &metricService) : AbstractHandler(), _logger(Poco::Logger::get("S3ServiceHandler")), _configuration(configuration), _metricService(metricService), _s3Service(configuration) {
  }

  void S3Handler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    try {

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "s3");
      //DumpRequest(request);

      // Get bucket key
      std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
      std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);

      if (userAgent.clientCommand == "ls" || userAgent.clientCommand == "rm") {

        if (bucket.empty() && key.empty()) {

          // Return bucket list
          Dto::S3::ListAllBucketResponse s3Response = _s3Service.ListAllBuckets();
          SendOkResponse(response, s3Response.ToXml());

        } else if (key.empty()) {

          if (Core::HttpUtils::HasQueryParameter(request.getURI(), "list-type")) {

            int listType = 1;
            if (Core::HttpUtils::HasQueryParameter(request.getURI(), "list-type")) {
              listType = std::stoi(Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "list-type"));
            }

            std::string delimiter;
            if (Core::HttpUtils::HasQueryParameter(request.getURI(), "delimiter")) {
              delimiter = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "delimiter");
            }

            std::string prefix;
            if (Core::HttpUtils::HasQueryParameter(request.getURI(), "prefix")) {
              prefix = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "prefix");
            }

            std::string encodingType = "url";
            if (Core::HttpUtils::HasQueryParameter(request.getURI(), "encoding_type")) {
              encodingType = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "encoding_type");
            }

            // Return object list
            Dto::S3::ListBucketRequest s3Request = {
                .region=region,
                .name=bucket,
                .listType=listType,
                .prefix=prefix,
                .delimiter=delimiter,
                .encodingType=encodingType
            };
            Dto::S3::ListBucketResult result = _s3Service.ListBucket(s3Request);
            SendOkResponse(response, result.ToXml());
          }
        }

      } else if (userAgent.clientCommand == "cp") {

        // Get object request
        log_debug_stream(_logger) << "S3 get object request, bucket: " << bucket << " key: " << key << std::endl;
        Dto::S3::GetObjectRequest s3Request = {
            .region=region,
            .bucket=bucket,
            .key=key
        };

        // Get version ID
        std::string versionId = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "versionId");
        if (!versionId.empty()) {
          s3Request.versionId = versionId;
        }

        // Get range
        if (request.has("Range")) {
          std::string rangeStr = request.get("Range");
          std::string parts = Core::StringUtils::Split(rangeStr, '=')[1];
          s3Request.min = std::stol(Core::StringUtils::Split(parts, '-')[0]);
          s3Request.max = std::stol(Core::StringUtils::Split(parts, '-')[1]);
          log_info_stream(_logger) << "Requested multipart download range: " << std::to_string(s3Request.min) << "-" << std::to_string(s3Request.max) << std::endl;
        }

        // Get object
        Dto::S3::GetObjectResponse s3Response = _s3Service.GetObject(s3Request);

        HeaderMap headerMap;
        headerMap["ETag"] = "\"" + s3Response.md5sum + "\"";
        headerMap["Content-Type"] = s3Response.contentType;
        headerMap["Last-Modified"] = Poco::DateTimeFormatter().format(s3Response.modified, Poco::DateTimeFormat::HTTP_FORMAT);

        // Set user headers
        for (const auto &m : s3Response.metadata) {
          headerMap["x-amz-meta-" + m.first] = m.second;
        }

        if (request.has("Range")) {
          long range = s3Request.max - s3Request.min + 1;
          headerMap["Accept-Ranges"] = "bytes";
          headerMap["Content-Range"] = "bytes " + std::to_string(s3Request.min) + "-" + std::to_string(s3Request.max) + "/" + std::to_string(s3Response.size);
          headerMap["Content-Length"] = std::to_string(range);
          log_info_stream(_logger) << "Progress: " << std::to_string(s3Request.min) << "-" << std::to_string(s3Request.max) << "/" << std::to_string(s3Response.size) << std::endl;

          SendRangeResponse(response, s3Response.filename, s3Request.min, s3Request.max, s3Response.size, headerMap);

        } else {

          SendOkResponse(response, s3Response.filename, s3Response.size, headerMap);

        }
      }
    } catch (Core::ServiceException &exc) {
      SendErrorResponse("S3", response, exc);
    }
  }

  void S3Handler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "s3");

      std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
      std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);
      log_debug_stream(_logger) << "Found bucket/key, bucket: " << bucket << " key: " << key << std::endl;

      bool isNotification = Core::HttpUtils::HasQueryParameter(request.getURI(), "notification");
      bool isVersioning = Core::HttpUtils::HasQueryParameter(request.getURI(), "versioning");

      if (isVersioning) {

        log_debug_stream(_logger) << "Bucket versioning request, region: " << region << " bucket: " << bucket << std::endl;

        std::string body = Core::HttpUtils::GetBodyAsString(request);

        Dto::S3::PutBucketVersioningRequest s3Request(body);
        s3Request.user = user;
        s3Request.region = region;
        s3Request.bucket = bucket;

        _s3Service.PutBucketVersioning(s3Request);

        SendNoContentResponse(response);

      } else if (isNotification) {

        log_debug_stream(_logger) << "Bucket notification request, bucket: " << bucket << std::endl;

        // S3 notification setup
        std::string body = Core::HttpUtils::GetBodyAsString(request);
        Dto::S3::PutBucketNotificationRequest s3Request = Dto::S3::PutBucketNotificationRequest(body, region, bucket);

        _s3Service.PutBucketNotification(s3Request);

        SendOkResponse(response);

      } else if (userAgent.clientCommand == "cp") {

        bool isMultipartUpload = Core::HttpUtils::HasQueryParameter(request.getURI(), "uploadId");

        if (isMultipartUpload) {

          // S3 initial multipart upload
          std::string partNumber = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "partNumber");
          std::string uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "uploadId");
          log_debug_stream(_logger) << "S3 multipart upload part: " << partNumber << std::endl;

          std::string eTag = _s3Service.UploadPart(request.stream(), std::stoi(partNumber), uploadId);

          HeaderMap headerMap;
          headerMap["ETag"] = eTag;

          SendNoContentResponse(response, headerMap);
          log_debug_stream(_logger) << "Finished S3 multipart upload part: " << partNumber << std::endl;

        } else {

          // Get the user metadata
          std::map<std::string, std::string> metadata = GetMetadata(request);

          bool isCopyRequest = HeaderExists(request, "x-amz-copy-source");

          if (isCopyRequest) {

            log_debug_stream(_logger) << "Object copy request, bucket: " << bucket << " key: " << key << std::endl;

            // Get S3 source bucket/key
            std::string sourceHeader = GetHeaderValue(request, "x-amz-copy-source", "empty");
            std::string sourceBucket = Core::HttpUtils::GetPathParameter(sourceHeader, 0);
            std::string sourceKey = Core::HttpUtils::GetPathParametersFromIndex(sourceHeader, 1);

            Dto::S3::CopyObjectRequest s3Request = {
                .region=region,
                .user=user,
                .sourceBucket=sourceBucket,
                .sourceKey= sourceKey,
                .targetBucket=bucket,
                .targetKey=key,
                .metadata=metadata
            };

            Dto::S3::CopyObjectResponse s3Response = _s3Service.CopyObject(s3Request);

            HeaderMap headerMap;
            headerMap["ETag"] = s3Response.eTag;

            SendOkResponse(response, s3Response.ToXml(), headerMap);

          } else {

            // S3 put object request
            Dto::S3::PutObjectRequest putObjectRequest = {
                .region=region,
                .bucket=bucket,
                .key=key,
                .owner=user,
                .md5Sum=GetHeaderValue(request, "Content-MD5", ""),
                .contentType=GetHeaderValue(request, "Content-Type", "application/octet-stream"),
                .contentLength=std::stol(GetHeaderValue(request, "Content-Length", "0")),
                .metadata=metadata
            };
            log_debug_stream(_logger) << "ContentLength: " << putObjectRequest.contentLength << " contentType: " << putObjectRequest.contentType << std::endl;

            Dto::S3::PutObjectResponse putObjectResponse = _s3Service.PutObject(putObjectRequest, request.stream());

            HeaderMap headerMap;
            headerMap["Content-MD5"] = putObjectResponse.md5Sum;
            headerMap["ETag"] = "\"" + putObjectResponse.etag + "\"";
            headerMap["x-amz-sdk-checksum-algorithm"] = putObjectResponse.checksumAlgorithm;
            headerMap["x-amz-checksum-sha256"] = putObjectResponse.checksumSha256;
            if (!putObjectResponse.versionId.empty()) {
              headerMap["x-amz-version-id"] = putObjectResponse.versionId;
            }
            log_debug_stream(_logger) << " size: " << putObjectResponse.contentLength << std::endl;

            SendOkResponse(response, {}, headerMap);
          }

        }
      } else if (userAgent.clientCommand == "mv") {

        log_debug_stream(_logger) << "Object move request, bucket: " << bucket << " key: " << key << std::endl;

        // Get S3 source bucket/key
        std::string sourceHeader = GetHeaderValue(request, "x-amz-copy-source", "empty");
        std::string sourceBucket = Core::HttpUtils::GetPathParameter(sourceHeader, 0);
        std::string sourceKey = Core::HttpUtils::GetPathParametersFromIndex(sourceHeader, 1);

        // Get the user metadata
        std::map<std::string, std::string> metadata = GetMetadata(request);

        Dto::S3::MoveObjectRequest s3Request = {
            .region=region,
            .user=user,
            .sourceBucket=sourceBucket,
            .sourceKey= sourceKey,
            .targetBucket=bucket,
            .targetKey=key,
            .metadata=metadata
        };

        Dto::S3::MoveObjectResponse s3Response = _s3Service.MoveObject(s3Request);

        HeaderMap headerMap;
        headerMap["ETag"] = s3Response.eTag;

        SendOkResponse(response, s3Response.ToXml(), headerMap);

      } else if (userAgent.clientCommand == "mb") {

        // S3 create bucket request
        std::string name = Core::DirUtils::RelativePath(request.getURI());
        std::string payload = Core::HttpUtils::GetBodyAsString(request);
        Dto::S3::CreateBucketRequest s3Request(payload);
        Dto::S3::CreateBucketResponse s3Response = _s3Service.CreateBucket(name, user, s3Request);

        SendOkResponse(response, s3Response.ToXml());

      }

    } catch (Poco::Exception &exc) {
      SendErrorResponse("S3", response, exc);
    }
  }

  void S3Handler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "s3");

      std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
      std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);

      if (userAgent.clientCommand == "cp") {

        bool isMultipartUpload = Core::HttpUtils::HasQueryParameter(request.getURI(), "uploads");
        bool isDeleteObjects = Core::HttpUtils::HasQueryParameter(request.getURI(), "delete");

        if (isMultipartUpload) {

          log_debug_stream(_logger) << "Starting multipart upload" << std::endl;

          Dto::S3::InitiateMultipartUploadResult result = _s3Service.CreateMultipartUpload(bucket, key, region, user);

          SendOkResponse(response, result.ToXml());

        } else if (isDeleteObjects) {

          log_debug_stream(_logger) << "Starting delete objects request" << std::endl;

          std::string payload = Core::HttpUtils::GetBodyAsString(request);

          auto s3Request = Dto::S3::DeleteObjectsRequest(payload);
          Dto::S3::DeleteObjectsResponse s3Response = _s3Service.DeleteObjects(s3Request);
          SendOkResponse(response, s3Response.ToXml());

        } else {

          std::string uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "uploadId");
          log_debug_stream(_logger) << "Finish multipart upload request, uploadId: " << uploadId << std::endl;

          Dto::S3::CompleteMultipartUploadResult result = _s3Service.CompleteMultipartUpload(uploadId, bucket, key, region, user);
          SendOkResponse(response, result.ToXml());

        }
      }

    } catch (Poco::Exception &exc) {
      SendErrorResponse("S3", response, exc);
    }
  }

  void S3Handler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      // Get user agent
      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "s3");

      if (userAgent.clientCommand == "rm") {

        // Get bucket / key
        std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
        std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);

        _s3Service.DeleteObject({.region=region, .user=user, .bucket=bucket, .key=key});
        SendDeleteResponse(response);

      } else if (userAgent.clientCommand == "rb") {

        // Get bucket / key
        std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);

        _s3Service.DeleteBucket(region, bucket);
        SendDeleteResponse(response);

      } else if (userAgent.clientCommand == "mv") {

        // Get bucket / key
        std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
        std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);

        _s3Service.DeleteObject({.region=region, .user=user, .bucket=bucket, .key=key});
        SendDeleteResponse(response);

      }

    } catch (Core::ServiceException &exc) {
      SendErrorResponse("S3", response, exc);
    }
  }

  void S3Handler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "S3 HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
      std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);
      log_debug_stream(_logger) << "S3 HEAD request, bucket: " << bucket << " key: " << key << std::endl;

      Dto::S3::GetMetadataRequest s3Request = {.region=region, .bucket=bucket, .key=key};
      Dto::S3::GetMetadataResponse s3Response = _s3Service.GetMetadata(s3Request);

      HeaderMap headerMap;
      headerMap["Server"] = "awsmock";
      headerMap["Content-Type"] = "application/json";
      headerMap["Last-Modified"] = Poco::DateTimeFormatter().format(s3Response.modified, Poco::DateTimeFormat::HTTP_FORMAT);
      headerMap["Content-Length"] = std::to_string(s3Response.size);
      headerMap["ETag"] = "\"" + s3Response.md5Sum + "\"";
      headerMap["accept-ranges"] = "bytes";
      headerMap["x-amz-id-2"] = Core::StringUtils::GenerateRandomString(30);
      headerMap["x-amz-request-id"] = Poco::UUIDGenerator().createRandom().toString();
      headerMap["x-amz-version-id"] = Core::StringUtils::GenerateRandomString(30);

      // User supplied metadata
      for (const auto &m : s3Response.metadata) {
        headerMap["x-amz-meta-" + m.first] = m.second;
      }
      SendHeadResponse(response, headerMap);

    } catch (Poco::Exception &exc) {
      log_warning_stream(_logger) << exc.message() << std::endl;
      SendErrorResponse("S3", response, exc);
    } catch (std::exception &exc) {
      log_error_stream(_logger) << exc.what() << std::endl;
    }
  }

  void S3Handler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "S3 OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
