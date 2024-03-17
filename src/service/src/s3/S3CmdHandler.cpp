
#include <awsmock/service/S3CmdHandler.h>

namespace AwsMock::Service {

  S3CmdHandler::S3CmdHandler(Core::Configuration &configuration, Core::MetricService &metricService) : AbstractHandler(), _logger(Poco::Logger::get("S3Handler")), _configuration(configuration), _metricService(metricService), _s3Service(configuration) {
  }

  void S3CmdHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
    log_debug_stream(_logger) << "S3 GET request, URI: " + request.getURI() << " region: " << s3ClientCommand.region << " user: " + s3ClientCommand.user << std::endl;

    try {

      switch (s3ClientCommand.command) {
        case Dto::Common::CommandType::LIST_BUCKETS: {

          Dto::S3::ListAllBucketResponse s3Response = _s3Service.ListAllBuckets();
          SendOkResponse(response, s3Response.ToXml());

          break;
        }
        case Dto::Common::CommandType::LIST_OBJECTS: {
          Dto::S3::ListBucketRequest s3Request;

          if (Core::HttpUtils::HasQueryParameter(request.getURI(), "list-type")) {

            int listType = std::stoi(Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "list-type"));

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
            s3Request = {
              .region=s3ClientCommand.region,
              .name=s3ClientCommand.bucket,
              .listType=listType,
              .prefix=prefix,
              .delimiter=delimiter,
              .encodingType=encodingType
            };

          } else {
            s3Request = {
              .region=s3ClientCommand.region,
              .name=s3ClientCommand.bucket,
              .listType=1,
              .encodingType="url"
            };
          }

          Dto::S3::ListBucketResponse s3Response = _s3Service.ListBucket(s3Request);
          SendOkResponse(response, s3Response.ToXml());
          break;
        }
        case Dto::Common::CommandType::GET_OBJECT: {

          // Get object request
          log_debug_stream(_logger) << "S3 get object request, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key << std::endl;
          Dto::S3::GetObjectRequest s3Request = {
            .region=s3ClientCommand.region,
            .bucket=s3ClientCommand.bucket,
            .key=s3ClientCommand.key
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
          headerMap["Last-Modified"] = Poco::DateTimeFormatter::format(s3Response.modified, Poco::DateTimeFormat::HTTP_FORMAT);

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
          break;
        }

          // Should not happen
        case Dto::Common::CommandType::CREATE_BUCKET:
        case Dto::Common::CommandType::PUT_OBJECT:
        case Dto::Common::CommandType::COPY_OBJECT:
        case Dto::Common::CommandType::MOVE_OBJECT:
        case Dto::Common::CommandType::DELETE_BUCKET:
        case Dto::Common::CommandType::DELETE_OBJECT:
        case Dto::Common::CommandType::DELETE_OBJECTS:
        case Dto::Common::CommandType::UNKNOWN: {
          log_error_stream(_logger) << "Bad request, method: GET clientCommand: " << Dto::Common::CommandTypeToString(s3ClientCommand.command) << std::endl;
          throw Core::ServiceException("Bad request, method: GET clientCommand: " + Dto::Common::CommandTypeToString(s3ClientCommand.command));
          break;
        }
      }
    } catch (Core::ServiceException &exc) {
      SendXmlErrorResponse("S3", response, exc);
    }
  }

  void S3CmdHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
    log_debug_stream(_logger) << "S3 PUT request, URI: " << request.getURI() << " region: " << s3ClientCommand.region << " user: " << s3ClientCommand.user << std::endl;

    try {

      switch (s3ClientCommand.command) {
        case Dto::Common::CommandType::CREATE_BUCKET: {

          Dto::S3::CreateBucketRequest s3Request = {.region=s3ClientCommand.region, .bucketName=s3ClientCommand.bucket, .bucketOwner=s3ClientCommand.user};
          Dto::S3::CreateBucketResponse s3Response = _s3Service.CreateBucket(s3Request);
          SendOkResponse(response, s3Response.ToXml());

          break;
        }
        case Dto::Common::CommandType::PUT_OBJECT: {

          // Get the user metadata
          std::map<std::string, std::string> metadata = GetMetadata(request);

          if (s3ClientCommand.copyRequest) {

            log_debug_stream(_logger) << "Object copy request, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key << std::endl;

            // Get S3 source bucket/key
            std::string sourceHeader = GetHeaderValue(request, "x-amz-copy-source", "empty");
            std::string sourceBucket = Core::HttpUtils::GetPathParameter(sourceHeader, 0);
            std::string sourceKey = Core::HttpUtils::GetPathParametersFromIndex(sourceHeader, 1);

            Dto::S3::CopyObjectRequest s3Request = {
              .region=s3ClientCommand.region,
              .user=s3ClientCommand.user,
              .sourceBucket=sourceBucket,
              .sourceKey= sourceKey,
              .targetBucket=s3ClientCommand.bucket,
              .targetKey=s3ClientCommand.key,
              .metadata=metadata
            };

            Dto::S3::CopyObjectResponse s3Response = _s3Service.CopyObject(s3Request);

            HeaderMap headerMap;
            headerMap["ETag"] = s3Response.eTag;

            SendOkResponse(response, s3Response.ToXml(), headerMap);

          } else {

            //DumpRequest(request);
            std::string checksumAlgorithm = GetHeaderValue(request, "x-amz-sdk-checksum-algorithm", "empty");

            // S3 put object request
            Dto::S3::PutObjectRequest putObjectRequest = {
              .region=s3ClientCommand.region,
              .bucket=s3ClientCommand.bucket,
              .key=s3ClientCommand.key,
              .owner=s3ClientCommand.user,
              .md5Sum=GetHeaderValue(request, "Content-MD5", ""),
              .contentType=GetHeaderValue(request, "Content-Type", "application/octet-stream"),
              .contentLength=std::stol(GetHeaderValue(request, "Content-Length", "0")),
              .checksumAlgorithm=checksumAlgorithm,
              .metadata=metadata
            };
            log_debug_stream(_logger) << "ContentLength: " << putObjectRequest.contentLength << " contentType: " << putObjectRequest.contentType << std::endl;

            Dto::S3::PutObjectResponse putObjectResponse = _s3Service.PutObject(putObjectRequest, request.stream());

            HeaderMap headerMap;
            //headerMap["Content-MD5"] = putObjectResponse.md5Sum;
            headerMap["ETag"] = Core::StringUtils::Quoted(putObjectResponse.md5Sum);
            if (!putObjectResponse.checksumSha1.empty()) {
              headerMap["x-amz-checksum-sha1"] = putObjectResponse.checksumSha1;
            }
            if (!putObjectResponse.checksumSha256.empty()) {
              headerMap["x-amz-checksum-sha256"] = putObjectResponse.checksumSha256;
            }
            if (!putObjectResponse.versionId.empty()) {
              headerMap["x-amz-version-id"] = putObjectResponse.versionId;
            }
            log_debug_stream(_logger) << " size: " << putObjectResponse.contentLength << std::endl;
            SendOkResponse(response, {}, headerMap);
          }
          break;
        }
        case Dto::Common::CommandType::MOVE_OBJECT: {
          log_debug_stream(_logger) << "Object move request, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key << std::endl;

          // Get S3 source bucket/key
          std::string sourceHeader = GetHeaderValue(request, "x-amz-copy-source", "empty");
          std::string sourceBucket = Core::HttpUtils::GetPathParameter(sourceHeader, 0);
          std::string sourceKey = Core::HttpUtils::GetPathParametersFromIndex(sourceHeader, 1);

          // Get the user metadata
          std::map<std::string, std::string> metadata = GetMetadata(request);

          Dto::S3::MoveObjectRequest s3Request = {
            .region=s3ClientCommand.region,
            .user=s3ClientCommand.user,
            .sourceBucket=sourceBucket,
            .sourceKey= sourceKey,
            .targetBucket=s3ClientCommand.bucket,
            .targetKey=s3ClientCommand.key,
            .metadata=metadata
          };

          Dto::S3::MoveObjectResponse s3Response = _s3Service.MoveObject(s3Request);

          HeaderMap headerMap;
          headerMap["ETag"] = s3Response.eTag;

          SendOkResponse(response, s3Response.ToXml(), headerMap);
          break;
        }
        case Dto::Common::CommandType::UPLOAD_PART: {

          std::string partNumber = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "partNumber");
          std::string uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "uploadId");
          log_debug_stream(_logger) << "S3 multipart upload part: " << partNumber << std::endl;

          std::string eTag = _s3Service.UploadPart(request.stream(), std::stoi(partNumber), uploadId);

          HeaderMap headerMap;
          headerMap["ETag"] = eTag;

          SendNoContentResponse(response, headerMap);
          log_debug_stream(_logger) << "Finished S3 multipart upload part: " << partNumber << std::endl;
          break;
        }

          // Should not happen
        case Dto::Common::CommandType::GET_OBJECT:
        case Dto::Common::CommandType::COPY_OBJECT:
        case Dto::Common::CommandType::LIST_BUCKETS:
        case Dto::Common::CommandType::LIST_OBJECTS:
        case Dto::Common::CommandType::DELETE_BUCKET:
        case Dto::Common::CommandType::DELETE_OBJECT:
        case Dto::Common::CommandType::DELETE_OBJECTS:
        case Dto::Common::CommandType::CREATE_MULTIPART_UPLOAD:
        case Dto::Common::CommandType::COMPLETE_MULTIPART_UPLOAD:
        case Dto::Common::CommandType::UNKNOWN: {
          log_error_stream(_logger) << "Bad request, method: PUT clientCommand: " << Dto::Common::CommandTypeToString(s3ClientCommand.command) << std::endl;
          throw Core::ServiceException("Bad request, method: PUT clientCommand: " + Dto::Common::CommandTypeToString(s3ClientCommand.command));
        }
      }

      if (s3ClientCommand.versionRequest) {

        log_debug_stream(_logger) << "Bucket versioning request, bucket: " << s3ClientCommand.bucket << std::endl;

        std::string body = Core::HttpUtils::GetBodyAsString(request);

        Dto::S3::PutBucketVersioningRequest s3Request(body);
        s3Request.user = s3ClientCommand.user;
        s3Request.region = s3ClientCommand.region;
        s3Request.bucket = s3ClientCommand.bucket;

        _s3Service.PutBucketVersioning(s3Request);

        SendNoContentResponse(response);

      } else if (s3ClientCommand.notificationRequest) {

        log_debug_stream(_logger) << "Bucket notification request, bucket: " << s3ClientCommand.bucket << std::endl;

        // S3 notification setup
        std::string body = Core::HttpUtils::GetBodyAsString(request);
        Dto::S3::PutBucketNotificationRequest s3Request = Dto::S3::PutBucketNotificationRequest(body, s3ClientCommand.region, s3ClientCommand.bucket);

        _s3Service.PutBucketNotification(s3Request);

        SendOkResponse(response);

      }

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("S3", response, exc);
    }
  }

  void S3CmdHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
    log_debug_stream(_logger) << "S3 POST request, URI: " << request.getURI() << " region: " << s3ClientCommand.region << " user: " << s3ClientCommand.user << std::endl;

    try {
      switch (s3ClientCommand.command) {
        case Dto::Common::CommandType::COPY_OBJECT: {
          if (s3ClientCommand.multipartRequest) {

            log_debug_stream(_logger) << "Starting multipart upload" << std::endl;

            Dto::S3::CreateMultipartUploadRequest s3Request = {.region=s3ClientCommand.region, .bucket=s3ClientCommand.bucket, .key=s3ClientCommand.key, .user=s3ClientCommand.user};
            Dto::S3::CreateMultipartUploadResult result = _s3Service.CreateMultipartUpload(s3Request);

            SendOkResponse(response, result.ToXml());

          } else {

            std::string uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "uploadId");
            log_debug_stream(_logger) << "Finish multipart upload request, uploadId: " << uploadId << std::endl;

            Dto::S3::CompleteMultipartUploadRequest s3Request = {.region=s3ClientCommand.region, .bucket=s3ClientCommand.bucket, .key=s3ClientCommand.key, .user=s3ClientCommand.user, .uploadId=uploadId};
            Dto::S3::CompleteMultipartUploadResult result = _s3Service.CompleteMultipartUpload(s3Request);
            SendOkResponse(response, result.ToXml());

          }
          break;
        }
        case Dto::Common::CommandType::DELETE_OBJECTS: {

          log_debug_stream(_logger) << "Starting delete objects request" << std::endl;

          std::string payload = Core::HttpUtils::GetBodyAsString(request);
          Dto::S3::DeleteObjectsRequest s3Request;
          s3Request.FromXml(payload);
          s3Request.region = s3ClientCommand.region;
          s3Request.bucket = s3ClientCommand.bucket;

          Dto::S3::DeleteObjectsResponse s3Response = _s3Service.DeleteObjects(s3Request);
          SendOkResponse(response, s3Response.ToXml());

          break;
        }
        case Dto::Common::CommandType::CREATE_MULTIPART_UPLOAD: {

          log_debug_stream(_logger) << "Starting multipart upload" << std::endl;

          Dto::S3::CreateMultipartUploadRequest s3Request = {.region=s3ClientCommand.region, .bucket=s3ClientCommand.bucket, .key=s3ClientCommand.key, .user=s3ClientCommand.user};
          Dto::S3::CreateMultipartUploadResult result = _s3Service.CreateMultipartUpload(s3Request);

          SendOkResponse(response, result.ToXml());
          break;
        }
        case Dto::Common::CommandType::COMPLETE_MULTIPART_UPLOAD: {

          log_debug_stream(_logger) << "Starting completing multipart upload" << std::endl;

          std::string uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "uploadId");
          Dto::S3::CompleteMultipartUploadRequest s3Request = {.region=s3ClientCommand.region, .bucket=s3ClientCommand.bucket, .key=s3ClientCommand.key, .user=s3ClientCommand.user, .uploadId=uploadId};
          Dto::S3::CompleteMultipartUploadResult result = _s3Service.CompleteMultipartUpload(s3Request);

          SendOkResponse(response, result.ToXml());
          break;
        }

          // Should not happen
        case Dto::Common::CommandType::CREATE_BUCKET:
        case Dto::Common::CommandType::LIST_BUCKETS:
        case Dto::Common::CommandType::DELETE_BUCKET:
        case Dto::Common::CommandType::LIST_OBJECTS:
        case Dto::Common::CommandType::PUT_OBJECT:
        case Dto::Common::CommandType::GET_OBJECT:
        case Dto::Common::CommandType::MOVE_OBJECT:
        case Dto::Common::CommandType::DELETE_OBJECT:
        case Dto::Common::CommandType::UPLOAD_PART:
        case Dto::Common::CommandType::UNKNOWN: {
          log_error_stream(_logger) << "Bad request, method: POST clientCommand: " << Dto::Common::CommandTypeToString(s3ClientCommand.command) << std::endl;
          throw Core::ServiceException("Bad request, method: POST clientCommand: " + Dto::Common::CommandTypeToString(s3ClientCommand.command));
        }
      }

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("S3", response, exc);
    }
  }

  void S3CmdHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
    log_debug_stream(_logger) << "S3 DELETE request, URI: " + request.getURI() << " region: " << s3ClientCommand.region << " user: " << s3ClientCommand.user << std::endl;

    try {

      switch (s3ClientCommand.command) {
        case Dto::Common::CommandType::DELETE_BUCKET: {

          Dto::S3::DeleteBucketRequest deleteBucketRequest = {.region=s3ClientCommand.region, .bucket=s3ClientCommand.bucket};
          _s3Service.DeleteBucket(deleteBucketRequest);
          SendDeleteResponse(response);
          break;
        }
        case Dto::Common::CommandType::MOVE_OBJECT:
        case Dto::Common::CommandType::DELETE_OBJECT: {

          _s3Service.DeleteObject({.region=s3ClientCommand.region, .user=s3ClientCommand.user, .bucket=s3ClientCommand.bucket, .key=s3ClientCommand.key});
          SendDeleteResponse(response);
          break;
        }

        // Should not happen
        case Dto::Common::CommandType::CREATE_BUCKET:
        case Dto::Common::CommandType::PUT_OBJECT:
        case Dto::Common::CommandType::GET_OBJECT:
        case Dto::Common::CommandType::COPY_OBJECT:
        case Dto::Common::CommandType::LIST_BUCKETS:
        case Dto::Common::CommandType::LIST_OBJECTS:
        case Dto::Common::CommandType::DELETE_OBJECTS:
        case Dto::Common::CommandType::CREATE_MULTIPART_UPLOAD:
        case Dto::Common::CommandType::UPLOAD_PART:
        case Dto::Common::CommandType::COMPLETE_MULTIPART_UPLOAD:
        case Dto::Common::CommandType::UNKNOWN: {
          log_error_stream(_logger) << "Bad request, method: DELETE clientCommand: " << Dto::Common::CommandTypeToString(s3ClientCommand.command) << std::endl;
        //  throw Core::ServiceException("Bad request, method: DELETE clientCommand: " + Dto::Common::CommandTypeToString(s3ClientCommand.command));
        }
      }

    } catch (Core::ServiceException &exc) {
      SendXmlErrorResponse("S3", response, exc);
    }
  }

  void S3CmdHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
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
      headerMap["Last-Modified"] = Poco::DateTimeFormatter::format(s3Response.modified, Poco::DateTimeFormat::HTTP_FORMAT);
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
      SendXmlErrorResponse("S3", response, exc);
    } catch (std::exception &exc) {
      log_error_stream(_logger) << exc.what() << std::endl;
    }
  }

  void S3CmdHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "S3 OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
