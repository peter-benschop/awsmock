
#include <awsmock/service/s3/S3CmdHandler.h>

namespace AwsMock::Service {

    void S3CmdHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
        log_debug << "S3 GET request, URI: " + request.getURI() << " region: " << s3ClientCommand.region << " user: " + s3ClientCommand.user;
        Core::MetricServiceTimer measure(S3_SERVICE_TIMER);

        try {

            switch (s3ClientCommand.command) {

                case Dto::Common::S3CommandType::LIST_BUCKETS: {

                    Dto::S3::ListAllBucketResponse s3Response = _s3Service.ListAllBuckets();
                    SendOkResponse(response, s3Response.ToXml());
                    log_info << "List buckets";

                    break;
                }

                case Dto::Common::S3CommandType::LIST_OBJECTS: {
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
                                .region = s3ClientCommand.region,
                                .name = s3ClientCommand.bucket,
                                .listType = listType,
                                .prefix = prefix,
                                .delimiter = delimiter,
                                .encodingType = encodingType};

                    } else {
                        s3Request = {
                                .region = s3ClientCommand.region,
                                .name = s3ClientCommand.bucket,
                                .listType = 1,
                                .encodingType = "url"};
                    }

                    Dto::S3::ListBucketResponse s3Response = _s3Service.ListBucket(s3Request);
                    SendOkResponse(response, s3Response.ToXml());
                    log_info << "List objects, bucket: " << s3ClientCommand.bucket;

                    break;
                }

                case Dto::Common::S3CommandType::GET_OBJECT: {

                    // Get object request
                    log_debug << "S3 get object request, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;
                    Dto::S3::GetObjectRequest s3Request = {
                            .region = s3ClientCommand.region,
                            .bucket = s3ClientCommand.bucket,
                            .key = s3ClientCommand.key};

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
                        log_info << "Requested multipart download range: " << std::to_string(s3Request.min) << "-" << std::to_string(s3Request.max);
                    }

                    // Get object
                    Dto::S3::GetObjectResponse s3Response = _s3Service.GetObject(s3Request);

                    HeaderMap headerMap;
                    headerMap["ETag"] = Core::StringUtils::Quoted(s3Response.md5sum);
                    headerMap["Content-Type"] = s3Response.contentType;
                    headerMap["Last-Modified"] = Poco::DateTimeFormatter::format(s3Response.modified, Poco::DateTimeFormat::HTTP_FORMAT);

                    // Set user headers
                    for (const auto &m: s3Response.metadata) {
                        headerMap["x-amz-meta-" + m.first] = m.second;
                    }

                    if (request.has("Range")) {
                        long size = s3Request.max - s3Request.max;
                        headerMap["Accept-Ranges"] = "bytes";
                        headerMap["Content-Range"] = "bytes " + std::to_string(s3Request.min) + "-" + std::to_string(s3Request.max) + "/" + std::to_string(s3Response.size);
                        headerMap["Content-Length"] = std::to_string(s3Response.size < size ? s3Response.size : size);
                        log_info << "Multi-part progress: " << std::to_string(s3Request.min) << "-" << std::to_string(s3Request.max) << "/" << std::to_string(s3Response.size);

                        SendRangeResponse(response, s3Response.filename, s3Request.min, s3Request.max, s3Response.size, headerMap);
                        log_info << "Multi-part range, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;

                    } else {

                        SendOkResponse(response, s3Response.filename, s3Response.size, headerMap);
                        log_info << "Get object, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;
                    }
                    break;
                }

                case Dto::Common::S3CommandType::LIST_OBJECT_VERSIONS: {

                    // Get object request
                    log_debug << "S3 list object versions request, bucket: " << s3ClientCommand.bucket << " prefix: " << s3ClientCommand.prefix;

                    std::string delimiter = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "delimiter");
                    std::string encodingType = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "encoding-type");
                    std::string keyMarker = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "key-marker");
                    std::string versionIdMarker = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "version-id-marker");
                    std::string sPageSize = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "max-keys");

                    // Convert maxKeys
                    int pageSize = 1000;
                    if (!sPageSize.empty()) {
                        pageSize = std::stoi(sPageSize);
                    }

                    // Build request
                    Dto::S3::ListObjectVersionsRequest s3Request = {
                            .region = s3ClientCommand.region,
                            .bucket = s3ClientCommand.bucket,
                            .prefix = s3ClientCommand.prefix,
                            .delimiter = delimiter,
                            .encodingType = encodingType,
                            .maxKeys = pageSize,
                            .versionIdMarker = versionIdMarker};

                    // Get object versions
                    Dto::S3::ListObjectVersionsResponse s3Response = _s3Service.ListObjectVersions(s3Request);

                    std::string tmp = s3Response.ToXml();
                    SendOkResponse(response, s3Response.ToXml());
                    log_info << "List object versions, bucket: " << s3ClientCommand.bucket << " prefix: " << s3ClientCommand.prefix;

                    break;
                }

                    // Should not happen
                case Dto::Common::S3CommandType::CREATE_BUCKET:
                case Dto::Common::S3CommandType::PUT_OBJECT:
                case Dto::Common::S3CommandType::COPY_OBJECT:
                case Dto::Common::S3CommandType::MOVE_OBJECT:
                case Dto::Common::S3CommandType::DELETE_BUCKET:
                case Dto::Common::S3CommandType::DELETE_OBJECT:
                case Dto::Common::S3CommandType::DELETE_OBJECTS:
                case Dto::Common::S3CommandType::CREATE_MULTIPART_UPLOAD:
                case Dto::Common::S3CommandType::UPLOAD_PART:
                case Dto::Common::S3CommandType::COMPLETE_MULTIPART_UPLOAD:
                case Dto::Common::S3CommandType::ABORT_MULTIPART_UPLOAD:
                case Dto::Common::S3CommandType::BUCKET_NOTIFICATION:
                case Dto::Common::S3CommandType::PUT_BUCKET_NOTIFICATION_CONFIGURATION:
                case Dto::Common::S3CommandType::PUT_BUCKET_ENCRYPTION:
                    break;
                case Dto::Common::S3CommandType::UNKNOWN: {
                    throw Core::ServiceException("Bad request, method: GET clientCommand: " + Dto::Common::S3CommandTypeToString(s3ClientCommand.command));
                }
            }
        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            SendXmlErrorResponse("S3", response, exc);
        } catch (std::exception &exc) {
            log_error << exc.what();
            SendXmlErrorResponse("S3", response, exc);
        }
    }

    void S3CmdHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
        log_debug << "S3 PUT request, URI: " << request.getURI() << " region: " << s3ClientCommand.region << " user: " << s3ClientCommand.user;
        Core::MetricServiceTimer measure(S3_SERVICE_TIMER);

        try {

            switch (s3ClientCommand.command) {

                case Dto::Common::S3CommandType::CREATE_BUCKET: {

                    Dto::S3::CreateBucketRequest s3Request = {.region = s3ClientCommand.region, .name = s3ClientCommand.bucket, .owner = s3ClientCommand.user};
                    Dto::S3::CreateBucketResponse s3Response = _s3Service.CreateBucket(s3Request);
                    SendOkResponse(response, s3Response.ToXml());
                    log_info << "Create bucket, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;

                    break;
                }

                case Dto::Common::S3CommandType::PUT_OBJECT: {

                    // Get the user metadata
                    std::map<std::string, std::string> metadata = GetMetadata(request);

                    if (s3ClientCommand.copyRequest) {

                        // Get S3 source bucket/key
                        std::string sourceHeader = GetHeaderValue(request, "x-amz-copy-source", "empty");
                        std::string sourceBucket = Core::HttpUtils::GetPathParameter(sourceHeader, 0);
                        std::string sourceKey = Core::HttpUtils::GetPathParametersFromIndex(sourceHeader, 1);

                        Dto::S3::CopyObjectRequest s3Request = {
                                .region = s3ClientCommand.region,
                                .user = s3ClientCommand.user,
                                .sourceBucket = sourceBucket,
                                .sourceKey = sourceKey,
                                .targetBucket = s3ClientCommand.bucket,
                                .targetKey = s3ClientCommand.key,
                                .metadata = metadata};

                        Dto::S3::CopyObjectResponse s3Response = _s3Service.CopyObject(s3Request);

                        SendOkResponse(response, s3Response.ToXml());
                        log_info << "Copy object, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;

                    } else {

                        //DumpRequest(request);
                        std::string checksumAlgorithm = GetHeaderValue(request, "x-amz-sdk-checksum-algorithm", "empty");

                        // S3 put object request
                        Dto::S3::PutObjectRequest putObjectRequest = {
                                .region = s3ClientCommand.region,
                                .bucket = s3ClientCommand.bucket,
                                .key = s3ClientCommand.key,
                                .owner = s3ClientCommand.user,
                                .md5Sum = GetHeaderValue(request, "Content-MD5", ""),
                                .contentType = GetHeaderValue(request, "Content-Type", "application/octet-stream"),
                                .contentLength = std::stol(GetHeaderValue(request, "Content-Length", "0")),
                                .checksumAlgorithm = checksumAlgorithm,
                                .metadata = metadata};
                        log_debug << "ContentLength: " << putObjectRequest.contentLength << " contentType: " << putObjectRequest.contentType;

                        Dto::S3::PutObjectResponse putObjectResponse = _s3Service.PutObject(putObjectRequest, request.stream());

                        log_info << "Put object, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key << " size: " << putObjectResponse.contentLength;
                        SendOkResponse(response, {});
                    }
                    break;
                }

                case Dto::Common::S3CommandType::MOVE_OBJECT: {
                    log_debug << "Object move request, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;

                    // Get S3 source bucket/key
                    std::string sourceHeader = GetHeaderValue(request, "x-amz-copy-source", "empty");
                    std::string sourceBucket = Core::HttpUtils::GetPathParameter(sourceHeader, 0);
                    std::string sourceKey = Core::HttpUtils::GetPathParametersFromIndex(sourceHeader, 1);

                    // Get the user metadata
                    std::map<std::string, std::string> metadata = GetMetadata(request);

                    Dto::S3::MoveObjectRequest s3Request = {
                            .region = s3ClientCommand.region,
                            .user = s3ClientCommand.user,
                            .sourceBucket = sourceBucket,
                            .sourceKey = sourceKey,
                            .targetBucket = s3ClientCommand.bucket,
                            .targetKey = s3ClientCommand.key,
                            .metadata = metadata};

                    Dto::S3::MoveObjectResponse s3Response = _s3Service.MoveObject(s3Request);

                    SendOkResponse(response, s3Response.ToXml());
                    log_info << "Move object, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;

                    break;
                }

                case Dto::Common::S3CommandType::UPLOAD_PART: {

                    std::string partNumber = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "partNumber");
                    std::string uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "uploadId");
                    log_debug << "S3 multipart upload part: " << partNumber;

                    std::string eTag = _s3Service.UploadPart(request.stream(), std::stoi(partNumber), uploadId);

                    HeaderMap headerMap;
                    headerMap["ETag"] = Core::StringUtils::Quoted(eTag);

                    SendNoContentResponse(response, headerMap);
                    log_debug << "Finished S3 multipart upload part: " << partNumber;

                    break;
                }

                case Dto::Common::S3CommandType::BUCKET_NOTIFICATION: {

                    log_debug << "Bucket notification request, bucket: " << s3ClientCommand.bucket;

                    // S3 notification setup
                    std::string body = Core::HttpUtils::GetBodyAsString(request);
                    Dto::S3::PutBucketNotificationRequest s3Request = Dto::S3::PutBucketNotificationRequest(body, s3ClientCommand.region, s3ClientCommand.bucket);

                    _s3Service.PutBucketNotification(s3Request);

                    SendOkResponse(response);

                    break;
                }

                case Dto::Common::S3CommandType::PUT_BUCKET_NOTIFICATION_CONFIGURATION: {

                    log_debug << "Put bucket notification configuration request, bucket: " << s3ClientCommand.bucket;

                    // S3 notification setup
                    std::string body = Core::HttpUtils::GetBodyAsString(request);
                    Dto::S3::PutBucketNotificationConfigurationRequest s3Request;
                    s3Request.FromXml(body);
                    s3Request.region = s3ClientCommand.region;
                    s3Request.bucket = s3ClientCommand.bucket;

                    Dto::S3::PutBucketNotificationConfigurationResponse s3Response = _s3Service.PutBucketNotificationConfiguration(s3Request);

                    SendOkResponse(response, s3Response.ToXml());
                    break;
                }

                case Dto::Common::S3CommandType::PUT_BUCKET_ENCRYPTION: {

                    log_debug << "Put bucket encryption configuration request, bucket: " << s3ClientCommand.bucket;

                    // S3 notification setup
                    std::string body = Core::HttpUtils::GetBodyAsString(request);
                    Dto::S3::PutBucketEncryptionRequest s3Request;
                    s3Request.FromXml(body);
                    s3Request.region = s3ClientCommand.region;
                    s3Request.bucket = s3ClientCommand.bucket;

                    _s3Service.PutBucketEncryption(s3Request);

                    SendOkResponse(response);
                    break;
                }

                    // Should not happen
                case Dto::Common::S3CommandType::GET_OBJECT:
                case Dto::Common::S3CommandType::COPY_OBJECT:
                case Dto::Common::S3CommandType::LIST_BUCKETS:
                case Dto::Common::S3CommandType::LIST_OBJECTS:
                case Dto::Common::S3CommandType::DELETE_BUCKET:
                case Dto::Common::S3CommandType::DELETE_OBJECT:
                case Dto::Common::S3CommandType::DELETE_OBJECTS:
                case Dto::Common::S3CommandType::CREATE_MULTIPART_UPLOAD:
                case Dto::Common::S3CommandType::COMPLETE_MULTIPART_UPLOAD:
                case Dto::Common::S3CommandType::ABORT_MULTIPART_UPLOAD:
                case Dto::Common::S3CommandType::LIST_OBJECT_VERSIONS:
                case Dto::Common::S3CommandType::UNKNOWN: {
                    log_error << "Bad request, method: PUT clientCommand: " << Dto::Common::S3CommandTypeToString(s3ClientCommand.command);
                    throw Core::ServiceException("Bad request, method: PUT clientCommand: " + Dto::Common::S3CommandTypeToString(s3ClientCommand.command));
                }
            }

            if (s3ClientCommand.versionRequest) {

                log_debug << "Bucket versioning request, bucket: " << s3ClientCommand.bucket;

                std::string body = Core::HttpUtils::GetBodyAsString(request);

                Dto::S3::PutBucketVersioningRequest s3Request(body);
                s3Request.user = s3ClientCommand.user;
                s3Request.region = s3ClientCommand.region;
                s3Request.bucket = s3ClientCommand.bucket;

                _s3Service.PutBucketVersioning(s3Request);

                SendNoContentResponse(response);
            }

        } catch (Core::ServiceException &exc) {
            log_error << exc.message();
            SendXmlErrorResponse("S3", response, exc);
        } catch (Core::JsonException &exc) {
            log_error << exc.message();
            SendXmlErrorResponse("S3", response, exc);
        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            SendXmlErrorResponse("S3", response, exc);
        } catch (std::exception &exc) {
            log_error << exc.what();
            SendXmlErrorResponse("S3", response, exc);
        }
    }

    void S3CmdHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
        log_debug << "S3 POST request, URI: " << request.getURI() << " region: " << s3ClientCommand.region << " user: " << s3ClientCommand.user;
        Core::MetricServiceTimer measure(S3_SERVICE_TIMER);

        try {
            switch (s3ClientCommand.command) {

                case Dto::Common::S3CommandType::COPY_OBJECT: {

                    if (s3ClientCommand.multipartRequest) {

                        log_debug << "Starting multipart upload";

                        Dto::S3::CreateMultipartUploadRequest s3Request = {.region = s3ClientCommand.region, .bucket = s3ClientCommand.bucket, .key = s3ClientCommand.key, .user = s3ClientCommand.user};
                        Dto::S3::CreateMultipartUploadResult result = _s3Service.CreateMultipartUpload(s3Request);

                        SendOkResponse(response, result.ToXml());
                        log_info << "Copy object, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;

                    } else {

                        std::string uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "uploadId");
                        log_debug << "Finish multipart upload request, uploadId: " << uploadId;

                        Dto::S3::CompleteMultipartUploadRequest s3Request = {.region = s3ClientCommand.region, .bucket = s3ClientCommand.bucket, .key = s3ClientCommand.key, .user = s3ClientCommand.user, .uploadId = uploadId};
                        Dto::S3::CompleteMultipartUploadResult result = _s3Service.CompleteMultipartUpload(s3Request);

                        HeaderMap headers;
                        headers["ETag"] = Core::StringUtils::Quoted(result.etag);

                        SendOkResponse(response, result.ToXml(), headers);
                        log_info << "Copy object, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;
                    }
                    break;
                }

                case Dto::Common::S3CommandType::DELETE_OBJECTS: {

                    //DumpRequest(request);
                    log_debug << "Starting delete objects request";

                    std::string payload = Core::HttpUtils::GetBodyAsString(request);
                    if (payload.empty()) {
                        return SendNoContentResponse(response);
                    }
                    Dto::S3::DeleteObjectsRequest s3Request;
                    s3Request.FromXml(payload);
                    s3Request.region = s3ClientCommand.region;
                    s3Request.bucket = s3ClientCommand.bucket;

                    Dto::S3::DeleteObjectsResponse s3Response = _s3Service.DeleteObjects(s3Request);
                    SendOkResponse(response, s3Response.ToXml());
                    log_info << "Object deleted, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;

                    break;
                }

                case Dto::Common::S3CommandType::CREATE_MULTIPART_UPLOAD: {

                    log_debug << "Starting multipart upload, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;

                    Dto::S3::CreateMultipartUploadRequest s3Request = {.region = s3ClientCommand.region, .bucket = s3ClientCommand.bucket, .key = s3ClientCommand.key, .user = s3ClientCommand.user};
                    Dto::S3::CreateMultipartUploadResult result = _s3Service.CreateMultipartUpload(s3Request);

                    SendOkResponse(response, result.ToXml());
                    log_info << "Create multi-part upload, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;

                    break;
                }

                case Dto::Common::S3CommandType::COMPLETE_MULTIPART_UPLOAD: {

                    log_debug << "Completing multipart upload, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;

                    std::string uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "uploadId");
                    Dto::S3::CompleteMultipartUploadRequest s3Request = {.region = s3ClientCommand.region, .bucket = s3ClientCommand.bucket, .key = s3ClientCommand.key, .user = s3ClientCommand.user, .uploadId = uploadId};
                    Dto::S3::CompleteMultipartUploadResult s3Response = _s3Service.CompleteMultipartUpload(s3Request);

                    HeaderMap headers;
                    headers["ETag"] = Core::StringUtils::Quoted(s3Response.etag);

                    SendOkResponse(response, s3Response.ToXml(), headers);
                    log_info << "Completed multipart upload, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;

                    break;
                }


                    // Should not happen
                case Dto::Common::S3CommandType::CREATE_BUCKET:
                case Dto::Common::S3CommandType::LIST_BUCKETS:
                case Dto::Common::S3CommandType::DELETE_BUCKET:
                case Dto::Common::S3CommandType::LIST_OBJECTS:
                case Dto::Common::S3CommandType::PUT_OBJECT:
                case Dto::Common::S3CommandType::GET_OBJECT:
                case Dto::Common::S3CommandType::MOVE_OBJECT:
                case Dto::Common::S3CommandType::DELETE_OBJECT:
                case Dto::Common::S3CommandType::UPLOAD_PART:
                case Dto::Common::S3CommandType::ABORT_MULTIPART_UPLOAD:
                case Dto::Common::S3CommandType::LIST_OBJECT_VERSIONS:
                case Dto::Common::S3CommandType::BUCKET_NOTIFICATION:
                case Dto::Common::S3CommandType::PUT_BUCKET_NOTIFICATION_CONFIGURATION:
                case Dto::Common::S3CommandType::PUT_BUCKET_ENCRYPTION:
                    break;
                case Dto::Common::S3CommandType::UNKNOWN: {
                    log_error << "Bad request, method: POST clientCommand: " << Dto::Common::S3CommandTypeToString(s3ClientCommand.command);
                    throw Core::ServiceException("Bad request, method: POST clientCommand: " + Dto::Common::S3CommandTypeToString(s3ClientCommand.command));
                }
            }

        } catch (Core::ServiceException &exc) {
            log_error << exc.message();
            SendXmlErrorResponse("S3", response, exc);
        } catch (Core::JsonException &exc) {
            log_error << exc.message();
            SendXmlErrorResponse("S3", response, exc);
        } catch (std::exception &exc) {
            log_error << exc.what();
            SendXmlErrorResponse("S3", response, exc);
        }
    }

    void S3CmdHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
        log_debug << "S3 DELETE request, URI: " + request.getURI() << " region: " << s3ClientCommand.region << " user: " << s3ClientCommand.user;
        Core::MetricServiceTimer measure(S3_SERVICE_TIMER);

        try {

            switch (s3ClientCommand.command) {

                case Dto::Common::S3CommandType::DELETE_BUCKET: {

                    Dto::S3::DeleteBucketRequest deleteBucketRequest = {.region = s3ClientCommand.region, .bucket = s3ClientCommand.bucket};
                    _s3Service.DeleteBucket(deleteBucketRequest);
                    SendDeleteResponse(response);
                    log_info << "Delete bucket, bucket: " << s3ClientCommand.bucket;

                    break;
                }

                case Dto::Common::S3CommandType::MOVE_OBJECT:
                case Dto::Common::S3CommandType::DELETE_OBJECT: {

                    _s3Service.DeleteObject({.region = s3ClientCommand.region, .user = s3ClientCommand.user, .bucket = s3ClientCommand.bucket, .key = s3ClientCommand.key});
                    SendDeleteResponse(response);
                    log_info << "Delete object, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;

                    break;
                }

                case Dto::Common::S3CommandType::ABORT_MULTIPART_UPLOAD: {

                    log_info << "Abort multipart upload request, bucket: " << s3ClientCommand.bucket << " key: " << s3ClientCommand.key;
                    SendNoContentResponse(response);

                    break;
                }

                    // Should not happen
                case Dto::Common::S3CommandType::CREATE_BUCKET:
                case Dto::Common::S3CommandType::PUT_OBJECT:
                case Dto::Common::S3CommandType::GET_OBJECT:
                case Dto::Common::S3CommandType::COPY_OBJECT:
                case Dto::Common::S3CommandType::LIST_BUCKETS:
                case Dto::Common::S3CommandType::LIST_OBJECTS:
                case Dto::Common::S3CommandType::DELETE_OBJECTS:
                case Dto::Common::S3CommandType::CREATE_MULTIPART_UPLOAD:
                case Dto::Common::S3CommandType::UPLOAD_PART:
                case Dto::Common::S3CommandType::COMPLETE_MULTIPART_UPLOAD:
                case Dto::Common::S3CommandType::LIST_OBJECT_VERSIONS:
                case Dto::Common::S3CommandType::BUCKET_NOTIFICATION:
                case Dto::Common::S3CommandType::PUT_BUCKET_NOTIFICATION_CONFIGURATION:
                case Dto::Common::S3CommandType::PUT_BUCKET_ENCRYPTION:
                case Dto::Common::S3CommandType::UNKNOWN: {
                    log_error << "Bad request, method: DELETE clientCommand: " << Dto::Common::S3CommandTypeToString(s3ClientCommand.command);
                    throw Core::ServiceException("Bad request, method: DELETE clientCommand: " + Dto::Common::S3CommandTypeToString(s3ClientCommand.command));
                }
            }

        } catch (Core::ServiceException &exc) {
            log_error << exc.message();
            SendXmlErrorResponse("S3", response, exc);
        } catch (Core::JsonException &exc) {
            log_error << exc.message();
            SendXmlErrorResponse("S3", response, exc);
        } catch (std::exception &exc) {
            log_error << exc.what();
            SendXmlErrorResponse("S3", response, exc);
        }
    }

    void S3CmdHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
        log_trace << "S3 HEAD request, URI: " << request.getURI() << " region: " << s3ClientCommand.region << " user: " << s3ClientCommand.user;
        Core::MetricServiceTimer measure(S3_SERVICE_TIMER);

        try {

            std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
            std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);
            log_debug << "S3 HEAD request, bucket: " << bucket << " key: " << key;

            Dto::S3::GetMetadataResponse s3Response;
            if (key.empty()) {
                Dto::S3::GetMetadataRequest s3Request = {.region = s3ClientCommand.region, .bucket = bucket};
                s3Response = _s3Service.GetBucketMetadata(s3Request);
            } else {
                Dto::S3::GetMetadataRequest s3Request = {.region = s3ClientCommand.region, .bucket = bucket, .key = key};
                s3Response = _s3Service.GetObjectMetadata(s3Request);
            }

            HeaderMap headerMap;
            headerMap["Server"] = "awsmock";
            headerMap["Content-Type"] = "application/json";
            headerMap["Last-Modified"] = Poco::DateTimeFormatter::format(s3Response.modified, Poco::DateTimeFormat::HTTP_FORMAT);
            headerMap["Content-Length"] = std::to_string(s3Response.size);
            //headerMap["ETag"] = "\"" + s3Response.md5Sum + "\"";
            headerMap["accept-ranges"] = "bytes";
            headerMap["x-amz-userPoolId-2"] = Core::StringUtils::GenerateRandomString(30);
            headerMap["x-amz-request-userPoolId"] = Poco::UUIDGenerator().createRandom().toString();
            headerMap["x-amz-version-userPoolId"] = Core::StringUtils::GenerateRandomString(30);
            headerMap["x-amz-bucket-region"] = s3Response.region;

            // User supplied metadata
            for (const auto &m: s3Response.metadata) {
                headerMap["x-amz-meta-" + m.first] = m.second;
            }
            for (const auto &m: request) {
                headerMap[m.first] = m.second;
            }
            SendHeadResponse(response, headerMap);

        } catch (Poco::Exception &exc) {
            log_warning << exc.message();
            SendXmlErrorResponse("S3", response, exc);
        } catch (std::exception &exc) {
            log_error << exc.what();
            SendXmlErrorResponse("S3", response, exc);
        }
    }
}// namespace AwsMock::Service
