
#include <awsmock/service/s3/S3Handler.h>

namespace AwsMock::Service {

    http::response<http::dynamic_body> S3Handler::HandleGetRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_debug << "S3 GET request, URI: " << request.target() << " region: " << region << " user: " + user;

        Dto::Common::S3ClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        log_debug << "S3 GET request, URI: " << request.target() << " region: " << clientCommand.region << " user: " + clientCommand.user;

        try {

            switch (clientCommand.command) {

                case Dto::Common::S3CommandType::LIST_BUCKETS: {

                    Dto::S3::ListAllBucketResponse s3Response = _s3Service.ListAllBuckets();
                    log_info << "List buckets";
                    return SendOkResponse(request, s3Response.ToXml());
                }

                case Dto::Common::S3CommandType::LIST_OBJECTS: {
                    Dto::S3::ListBucketRequest s3Request;

                    if (Core::HttpUtils::HasQueryParameter(request.target(), "list-type")) {

                        int listType = std::stoi(Core::HttpUtils::GetQueryParameterValueByName(request.target(), "list-type"));

                        std::string delimiter;
                        if (Core::HttpUtils::HasQueryParameter(request.target(), "delimiter")) {
                            delimiter = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "delimiter");
                        }

                        std::string prefix;
                        if (Core::HttpUtils::HasQueryParameter(request.target(), "prefix")) {
                            prefix = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "prefix");
                        }

                        std::string encodingType = "url";
                        if (Core::HttpUtils::HasQueryParameter(request.target(), "encoding_type")) {
                            encodingType = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "encoding_type");
                        }

                        // Return object list
                        s3Request = {
                                .region = clientCommand.region,
                                .name = clientCommand.bucket,
                                .listType = listType,
                                .prefix = prefix,
                                .delimiter = delimiter,
                                .encodingType = encodingType};

                    } else {
                        s3Request = {
                                .region = clientCommand.region,
                                .name = clientCommand.bucket,
                                .listType = 1,
                                .encodingType = "url"};
                    }

                    Dto::S3::ListBucketResponse s3Response = _s3Service.ListBucket(s3Request);

                    log_info << "List objects, bucket: " << clientCommand.bucket;
                    return SendOkResponse(request, s3Response.ToXml());
                }

                case Dto::Common::S3CommandType::GET_OBJECT: {

                    // Get object request
                    log_debug << "S3 get object request, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;
                    Dto::S3::GetObjectRequest s3Request = {
                            .region = clientCommand.region,
                            .bucket = clientCommand.bucket,
                            .key = clientCommand.key};

                    // Get version ID
                    std::string versionId = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "versionId");
                    if (!versionId.empty()) {
                        s3Request.versionId = versionId;
                    }

                    // Get range
                    long size;
                    GetRange(request, s3Request.min, s3Request.max, size);

                    // Get object
                    Dto::S3::GetObjectResponse s3Response = _s3Service.GetObject(s3Request);

                    std::map<std::string, std::string> headerMap;
                    headerMap["ETag"] = Core::StringUtils::Quoted(s3Response.md5sum);
                    headerMap["Content-Type"] = s3Response.contentType;
                    headerMap["Last-Modified"] = Core::DateTimeUtils::HttpFormat(s3Response.modified);

                    // Set user headers
                    for (const auto &m: s3Response.metadata) {
                        headerMap["x-amz-meta-" + m.first] = m.second;
                    }

                    if (Core::HttpUtils::HasHeader(request, "Range")) {
                        headerMap["Accept-Ranges"] = "bytes";
                        headerMap["Content-Range"] = "bytes " + std::to_string(s3Request.min) + "-" + std::to_string(s3Request.max) + "/" + std::to_string(s3Response.size);
                        headerMap["Content-Length"] = std::to_string(size);
                        log_info << "Multi-part download progress: " << std::to_string(s3Request.min) << "-" << std::to_string(s3Request.max) << "/" << std::to_string(s3Response.size);
                        log_info << "Multi-part download request range, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;

                        return SendRangeResponse(request, s3Response.filename, s3Request.min, s3Request.max, size, s3Response.size, headerMap);

                    } else {

                        log_info << "Get object, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;
                        return SendOkResponse(request, s3Response.filename, s3Response.size, headerMap);
                    }
                }

                case Dto::Common::S3CommandType::LIST_OBJECT_VERSIONS: {

                    // Get object request
                    log_debug << "S3 list object versions request, bucket: " << clientCommand.bucket << " prefix: " << clientCommand.prefix;

                    std::string delimiter = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "delimiter");
                    std::string encodingType = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "encoding-type");
                    std::string keyMarker = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "key-marker");
                    std::string versionIdMarker = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "version-id-marker");
                    std::string sPageSize = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "max-keys");

                    // Convert maxKeys
                    int pageSize = 1000;
                    if (!sPageSize.empty()) {
                        pageSize = std::stoi(sPageSize);
                    }

                    // Build request
                    Dto::S3::ListObjectVersionsRequest s3Request = {
                            .region = clientCommand.region,
                            .bucket = clientCommand.bucket,
                            .prefix = clientCommand.prefix,
                            .delimiter = delimiter,
                            .encodingType = encodingType,
                            .maxKeys = pageSize,
                            .versionIdMarker = versionIdMarker};

                    // Get object versions
                    Dto::S3::ListObjectVersionsResponse s3Response = _s3Service.ListObjectVersions(s3Request);

                    log_info << "List object versions, bucket: " << clientCommand.bucket << " prefix: " << clientCommand.prefix;
                    return SendOkResponse(request, s3Response.ToXml());
                }

                    // Delete object (rm) with recursive option, issues first a list request
                case Dto::Common::S3CommandType::DELETE_OBJECT: {

                    Dto::S3::ListBucketRequest s3Request;

                    if (Core::HttpUtils::HasQueryParameter(request.target(), "list-type")) {

                        int listType = std::stoi(Core::HttpUtils::GetQueryParameterValueByName(request.target(), "list-type"));

                        std::string delimiter;
                        if (Core::HttpUtils::HasQueryParameter(request.target(), "delimiter")) {
                            delimiter = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "delimiter");
                        }

                        std::string prefix;
                        if (Core::HttpUtils::HasQueryParameter(request.target(), "prefix")) {
                            prefix = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "prefix");
                        }

                        std::string encodingType = "url";
                        if (Core::HttpUtils::HasQueryParameter(request.target(), "encoding_type")) {
                            encodingType = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "encoding_type");
                        }

                        // Return object list
                        s3Request = {
                                .region = clientCommand.region,
                                .name = clientCommand.bucket,
                                .listType = listType,
                                .prefix = prefix,
                                .delimiter = delimiter,
                                .encodingType = encodingType};

                    } else {
                        s3Request = {
                                .region = clientCommand.region,
                                .name = clientCommand.bucket,
                                .listType = 1,
                                .encodingType = "url"};
                    }

                    Dto::S3::ListBucketResponse s3Response = _s3Service.ListBucket(s3Request);
                    log_info << "List objects, bucket: " << clientCommand.bucket;
                    return SendOkResponse(request, s3Response.ToXml());
                }

                    // Should not happen
                case Dto::Common::S3CommandType::CREATE_BUCKET:
                case Dto::Common::S3CommandType::PUT_OBJECT:
                case Dto::Common::S3CommandType::COPY_OBJECT:
                case Dto::Common::S3CommandType::MOVE_OBJECT:
                case Dto::Common::S3CommandType::DELETE_BUCKET:
                case Dto::Common::S3CommandType::DELETE_OBJECTS:
                case Dto::Common::S3CommandType::CREATE_MULTIPART_UPLOAD:
                case Dto::Common::S3CommandType::UPLOAD_PART:
                case Dto::Common::S3CommandType::COMPLETE_MULTIPART_UPLOAD:
                case Dto::Common::S3CommandType::ABORT_MULTIPART_UPLOAD:
                case Dto::Common::S3CommandType::BUCKET_NOTIFICATION:
                case Dto::Common::S3CommandType::PUT_BUCKET_NOTIFICATION_CONFIGURATION:
                case Dto::Common::S3CommandType::PUT_BUCKET_ENCRYPTION:
                case Dto::Common::S3CommandType::UNKNOWN:
                default:
                    log_error << "Unknown method";
                    return SendBadRequestError(request, "Unknown method");
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (std::exception &exc) {
            log_error << exc.what();
            return SendInternalServerError(request, exc.what());
        }
        return SendBadRequestError(request, "Unknown method");
    }

    http::response<http::dynamic_body> S3Handler::HandlePutRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(S3_SERVICE_TIMER);
        log_debug << "S3 PUT request, URI: " << request.target() << " region: " << region << " user: " << user;

        Dto::Common::S3ClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        log_debug << "S3 PUT request, URI: " << request.target() << " region: " << clientCommand.region << " user: " << clientCommand.user;

        try {

            switch (clientCommand.command) {

                case Dto::Common::S3CommandType::CREATE_BUCKET: {

                    Dto::S3::CreateBucketRequest s3Request = {.region = clientCommand.region, .name = clientCommand.bucket, .owner = clientCommand.user};
                    Dto::S3::CreateBucketResponse s3Response = _s3Service.CreateBucket(s3Request);
                    return SendOkResponse(request, s3Response.ToXml());
                    log_info << "Create bucket, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;
                }

                case Dto::Common::S3CommandType::PUT_OBJECT: {

                    //Core::HttpUtils::DumpHeaders(request);

                    // Get the user metadata
                    std::map<std::string, std::string> metadata = GetMetadata(request);

                    if (clientCommand.copyRequest) {

                        // Get S3 source bucket/key
                        std::string sourceHeader = request["x-amz-copy-source"];
                        std::string sourceBucket = Core::HttpUtils::GetPathParameter(sourceHeader, 0);
                        std::string sourceKey = Core::HttpUtils::GetPathParametersFromIndex(sourceHeader, 1);

                        Dto::S3::CopyObjectRequest s3Request = {
                                .region = clientCommand.region,
                                .user = clientCommand.user,
                                .sourceBucket = sourceBucket,
                                .sourceKey = sourceKey,
                                .targetBucket = clientCommand.bucket,
                                .targetKey = clientCommand.key,
                                .metadata = metadata};

                        Dto::S3::CopyObjectResponse s3Response = _s3Service.CopyObject(s3Request);

                        return SendOkResponse(request, s3Response.ToXml());
                        log_info << "Copy object, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;

                    } else {

                        // Checksum
                        std::string checksumAlgorithm = Core::HttpUtils::GetHeaderValue(request, "x-amz-sdk-checksum-algorithm");
                        bool chunckedEncoding = Core::StringUtils::ContainsIgnoreCase(Core::HttpUtils::GetHeaderValue(request, "Content-Encoding"), "aws-chunked");

                        // S3 put object request
                        Dto::S3::PutObjectRequest putObjectRequest = {
                                .region = clientCommand.region,
                                .bucket = clientCommand.bucket,
                                .key = clientCommand.key,
                                .owner = clientCommand.user,
                                .md5Sum = request["Content-MD5"],
                                .contentType = request["Content-Type"],
                                .checksumAlgorithm = checksumAlgorithm,
                                .metadata = metadata};

                        boost::beast::net::streambuf sb;
                        sb.commit(boost::beast::net::buffer_copy(sb.prepare(request.body().size()), request.body().cdata()));
                        std::istream stream(&sb);

                        log_debug << "ContentLength: " << putObjectRequest.contentLength << " contentType: " << putObjectRequest.contentType;

                        Dto::S3::PutObjectResponse putObjectResponse = _s3Service.PutObject(putObjectRequest, stream, chunckedEncoding);
                        stream.clear();

                        log_info << "Put object, bucket: " << clientCommand.bucket << " key: " << clientCommand.key << " size: " << putObjectResponse.contentLength;
                        return SendOkResponse(request);
                    }
                }

                case Dto::Common::S3CommandType::MOVE_OBJECT: {
                    log_debug << "Object move request, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;

                    // Get S3 source bucket/key
                    std::string sourceHeader = Core::HttpUtils::GetHeaderValue(request, "x-amz-copy-source");
                    std::string sourceBucket = Core::HttpUtils::GetPathParameter(sourceHeader, 0);
                    std::string sourceKey = Core::HttpUtils::GetPathParametersFromIndex(sourceHeader, 1);

                    // Get the user metadata
                    //std::map<std::string, std::string> metadata = GetMetadata(request);

                    Dto::S3::MoveObjectRequest s3Request = {
                            .region = clientCommand.region,
                            .user = clientCommand.user,
                            .sourceBucket = sourceBucket,
                            .sourceKey = sourceKey,
                            .targetBucket = clientCommand.bucket,
                            .targetKey = clientCommand.key,
                            //        .metadata = metadata
                    };

                    Dto::S3::MoveObjectResponse s3Response = _s3Service.MoveObject(s3Request);

                    return SendOkResponse(request, s3Response.ToXml());
                    log_info << "Move object, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;
                }

                case Dto::Common::S3CommandType::UPLOAD_PART: {

                    std::string partNumber = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "partNumber");
                    std::string uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "uploadId");
                    std::string contentLength = request.base()[http::field::content_length];
                    log_debug << "S3 multipart upload part: " << partNumber << " size: " << contentLength;

                    boost::beast::net::streambuf sb;
                    sb.commit(boost::beast::net::buffer_copy(sb.prepare(request.body().size()), request.body().cdata()));
                    std::istream stream(&sb);

                    std::string eTag = _s3Service.UploadPart(stream, std::stoi(partNumber), uploadId);
                    stream.clear();

                    std::map<std::string, std::string> headerMap;
                    headerMap["ETag"] = Core::StringUtils::Quoted(eTag);
                    log_debug << "Finished S3 multipart upload part: " << partNumber;

                    return SendOkResponse(request, {}, headerMap);
                }

                case Dto::Common::S3CommandType::UPLOAD_PART_COPY: {

                    std::string partNumber = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "partNumber");
                    std::string uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "uploadId");

                    // Get range
                    Dto::S3::UploadPartCopyRequest s3Request;
                    s3Request.region = region;
                    s3Request.uploadId = uploadId;
                    s3Request.partNumber = std::stoi(partNumber);
                    s3Request.targetBucket = clientCommand.bucket;
                    s3Request.targetKey = clientCommand.key;

                    // Get S3 source bucket/key
                    std::string sourceHeader = Core::HttpUtils::GetHeaderValue(request, "x-amz-copy-source");
                    std::string sourceBucket = Core::HttpUtils::GetPathParameter(sourceHeader, 0);
                    std::string sourceKey = Core::HttpUtils::GetPathParametersFromIndex(sourceHeader, 1);
                    s3Request.sourceBucket = sourceBucket;
                    s3Request.sourceKey = sourceKey;

                    if (Core::HttpUtils::HasHeader(request, "x-amz-copy-source-range")) {
                        std::string rangeStr = Core::HttpUtils::GetHeaderValue(request, "x-amz-copy-source-range");
                        std::string parts = Core::StringUtils::Split(rangeStr, '=')[1];
                        s3Request.min = std::stol(Core::StringUtils::Split(parts, '-')[0]);
                        s3Request.max = std::stol(Core::StringUtils::Split(parts, '-')[1]);
                        log_info << "Requested multipart download range: " << std::to_string(s3Request.min) << "-" << std::to_string(s3Request.max);
                    }
                    log_debug << "S3 multipart upload part copy: " << partNumber;

                    Dto::S3::UploadPartCopyResponse s3Response = _s3Service.UploadPartCopy(s3Request);

                    log_debug << "Finished S3 multipart upload part copy: " << partNumber;

                    return SendOkResponse(request, s3Response.ToXml());
                }

                case Dto::Common::S3CommandType::BUCKET_NOTIFICATION: {

                    log_debug << "Bucket notification request, bucket: " << clientCommand.bucket;

                    // S3 notification setup
                    std::string body = Core::HttpUtils::GetBodyAsString(request);
                    Dto::S3::PutBucketNotificationRequest s3Request = Dto::S3::PutBucketNotificationRequest(body, clientCommand.region, clientCommand.bucket);

                    _s3Service.PutBucketNotification(s3Request);

                    return SendNoContentResponse(request);
                }

                case Dto::Common::S3CommandType::PUT_BUCKET_NOTIFICATION_CONFIGURATION: {

                    log_debug << "Put bucket notification configuration request, bucket: " << clientCommand.bucket;

                    // S3 notification setup
                    std::string body = Core::HttpUtils::GetBodyAsString(request);
                    Dto::S3::PutBucketNotificationConfigurationRequest s3Request;
                    s3Request.FromXml(body);
                    s3Request.region = clientCommand.region;
                    s3Request.bucket = clientCommand.bucket;

                    Dto::S3::PutBucketNotificationConfigurationResponse s3Response = _s3Service.PutBucketNotificationConfiguration(s3Request);

                    return SendOkResponse(request, s3Response.ToXml());
                }

                case Dto::Common::S3CommandType::PUT_BUCKET_ENCRYPTION: {

                    log_debug << "Put bucket encryption configuration request, bucket: " << clientCommand.bucket;

                    // S3 notification setup
                    //std::string body = Core::HttpUtils::GetBodyAsString(request);
                    Dto::S3::PutBucketEncryptionRequest s3Request;
                    //s3Request.FromXml(body);
                    s3Request.region = clientCommand.region;
                    s3Request.bucket = clientCommand.bucket;

                    _s3Service.PutBucketEncryption(s3Request);

                    return SendOkResponse(request);
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
                    log_error << "Bad request, method: PUT clientCommand: " << Dto::Common::S3CommandTypeToString(clientCommand.command);
                    return SendBadRequestError(request, "Unknown method");
                }
                default:
                    log_error << "Bad request, method: PUT clientCommand: " << Dto::Common::S3CommandTypeToString(clientCommand.command);
                    return SendBadRequestError(request, "Unknown method");
            }

            if (clientCommand.versionRequest) {

                log_debug << "Bucket versioning request, bucket: " << clientCommand.bucket;

                std::string body = Core::HttpUtils::GetBodyAsString(request);

                Dto::S3::PutBucketVersioningRequest s3Request(body);
                s3Request.user = clientCommand.user;
                s3Request.region = clientCommand.region;
                s3Request.bucket = clientCommand.bucket;

                _s3Service.PutBucketVersioning(s3Request);

                return SendNoContentResponse(request);
            }
        } catch (Core::ServiceException &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (Core::JsonException &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (std::exception &exc) {
            log_error << exc.what();
            return SendInternalServerError(request, exc.what());
        }
        return SendBadRequestError(request, "Unknown method");
    }

    http::response<http::dynamic_body> S3Handler::HandlePostRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_debug << "S3 POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        Dto::Common::S3ClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        try {
            switch (clientCommand.command) {

                case Dto::Common::S3CommandType::COPY_OBJECT: {

                    if (clientCommand.multipartRequest) {

                        log_debug << "Starting multipart upload";

                        Dto::S3::CreateMultipartUploadRequest s3Request = {.region = clientCommand.region, .bucket = clientCommand.bucket, .key = clientCommand.key, .user = clientCommand.user};
                        Dto::S3::CreateMultipartUploadResult result = _s3Service.CreateMultipartUpload(s3Request);

                        return SendOkResponse(request, result.ToXml());
                        log_info << "Copy object, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;

                    } else {

                        std::string uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "uploadId");
                        log_debug << "Finish multipart upload request, uploadId: " << uploadId;

                        Dto::S3::CompleteMultipartUploadRequest s3Request = {.region = clientCommand.region, .bucket = clientCommand.bucket, .key = clientCommand.key, .user = clientCommand.user, .uploadId = uploadId};
                        Dto::S3::CompleteMultipartUploadResult result = _s3Service.CompleteMultipartUpload(s3Request);

                        std::map<std::string, std::string> headers;
                        headers["ETag"] = Core::StringUtils::Quoted(result.etag);

                        log_info << "Copy object, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;
                        return SendOkResponse(request, result.ToXml(), headers);
                    }
                }

                case Dto::Common::S3CommandType::DELETE_OBJECTS: {

                    log_debug << "Starting delete objects request";

                    const std::string &payload = Core::HttpUtils::GetBodyAsString(request);
                    if (payload.empty()) {
                        return SendNoContentResponse(request);
                    }
                    Dto::S3::DeleteObjectsRequest s3Request;
                    s3Request.FromXml(payload);
                    s3Request.region = clientCommand.region;
                    s3Request.bucket = clientCommand.bucket;

                    Dto::S3::DeleteObjectsResponse s3Response = _s3Service.DeleteObjects(s3Request);
                    log_info << "Object deleted, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;
                    return SendOkResponse(request, s3Response.ToXml());
                }

                case Dto::Common::S3CommandType::CREATE_MULTIPART_UPLOAD: {

                    log_debug << "Starting multipart upload, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;
                    //Core::HttpUtils::DumpHeaders(request);

                    Dto::S3::CreateMultipartUploadRequest s3Request = {.region = clientCommand.region, .bucket = clientCommand.bucket, .key = clientCommand.key, .user = clientCommand.user};
                    s3Request.metadata = GetMetadata(request);

                    Dto::S3::CreateMultipartUploadResult result = _s3Service.CreateMultipartUpload(s3Request);

                    log_info << "Create multi-part upload, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;
                    return SendOkResponse(request, result.ToXml());
                }

                case Dto::Common::S3CommandType::COMPLETE_MULTIPART_UPLOAD: {

                    log_debug << "Completing multipart upload, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;

                    //Core::HttpUtils::DumpHeaders(request);
                    std::string uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "uploadId");
                    Dto::S3::CompleteMultipartUploadRequest s3Request = {.region = clientCommand.region, .bucket = clientCommand.bucket, .key = clientCommand.key, .user = clientCommand.user, .uploadId = uploadId};
                    Dto::S3::CompleteMultipartUploadResult s3Response = _s3Service.CompleteMultipartUpload(s3Request);

                    std::map<std::string, std::string> headers;
                    headers["ETag"] = Core::StringUtils::Quoted(s3Response.etag);

                    log_info << "Completed multipart upload, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;
                    return SendOkResponse(request, s3Response.ToXml(), headers);
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
                    log_error << "Unknown method";
                    return SendBadRequestError(request, "Unknown method");
                }

                default:
                    log_error << "Unknown method";
                    return SendBadRequestError(request, "Unknown method");
            }

        } catch (Core::ServiceException &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (Core::JsonException &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (std::exception &exc) {
            log_error << exc.what();
            return SendInternalServerError(request, exc.what());
        }
        log_error << "Unknown method";
        return SendBadRequestError(request, "Unknown method");
    }

    http::response<http::dynamic_body> S3Handler::HandleDeleteRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_debug << "S3 DELETE request, URI: " << request.target() << " region: " << region << " user: " << user;

        Dto::Common::S3ClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        try {

            switch (clientCommand.command) {

                case Dto::Common::S3CommandType::DELETE_BUCKET: {

                    Dto::S3::DeleteBucketRequest deleteBucketRequest = {.region = clientCommand.region, .bucket = clientCommand.bucket};
                    _s3Service.DeleteBucket(deleteBucketRequest);

                    log_info << "Delete bucket, bucket: " << clientCommand.bucket;
                    return SendNoContentResponse(request);
                }

                case Dto::Common::S3CommandType::MOVE_OBJECT:
                case Dto::Common::S3CommandType::DELETE_OBJECT: {

                    _s3Service.DeleteObject({.region = clientCommand.region, .user = clientCommand.user, .bucket = clientCommand.bucket, .key = clientCommand.key});
                    log_info << "Delete object, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;
                    return SendNoContentResponse(request);
                }

                case Dto::Common::S3CommandType::ABORT_MULTIPART_UPLOAD: {

                    log_info << "Abort multipart upload request, bucket: " << clientCommand.bucket << " key: " << clientCommand.key;
                    return SendNoContentResponse(request);
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
                    log_error << "Unknown method";
                    return SendBadRequestError(request, "Unknown method");
                }
                default:
                    log_error << "Unknown method";
                    return SendBadRequestError(request, "Unknown method");
            }

        } catch (Core::ServiceException &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (Core::JsonException &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (std::exception &exc) {
            log_error << exc.what();
            return SendInternalServerError(request, exc.what());
        }
    }

    http::response<http::dynamic_body> S3Handler::HandleHeadRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_trace << "S3 HEAD request, URI: " << request.target() << " region: " << region << " user: " << user;

        Dto::Common::S3ClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        try {

            Dto::S3::GetMetadataResponse s3Response;
            if (clientCommand.key.empty()) {

                // Bucket metadata
                Dto::S3::GetMetadataRequest s3Request = {.region = clientCommand.region, .bucket = clientCommand.bucket};
                s3Response = _s3Service.GetBucketMetadata(s3Request);

            } else {

                // Object metadata
                Dto::S3::GetMetadataRequest s3Request = {.region = clientCommand.region, .bucket = clientCommand.bucket, .key = clientCommand.key};
                s3Response = _s3Service.GetObjectMetadata(s3Request);
            }

            std::map<std::string, std::string> headers;
            headers["Handler"] = "awsmock";
            headers["Content-Type"] = "application/json";
            headers["Last-Modified"] = Core::DateTimeUtils::HttpFormat(s3Response.modified);
            headers["Content-Length"] = std::to_string(s3Response.size);
            headers["ETag"] = "\"" + s3Response.md5Sum + "\"";
            headers["accept-ranges"] = "bytes";
            headers["x-amz-userPoolId-2"] = Core::StringUtils::GenerateRandomString(30);
            headers["x-amz-request-userPoolId"] = Poco::UUIDGenerator().createRandom().toString();
            headers["x-amz-version-userPoolId"] = Core::StringUtils::GenerateRandomString(30);
            headers["x-amz-bucket-region"] = s3Response.region;
            headers["x-amz-location-name"] = s3Response.region;

            // User supplied metadata
            for (const auto &m: s3Response.metadata) {
                headers["x-amz-meta-" + m.first] = m.second;
            }

            return SendOkResponse(request, {}, headers);

        } catch (Poco::Exception &exc) {
            log_warning << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (std::exception &exc) {
            log_error << exc.what();
            return SendInternalServerError(request, exc.what());
        }
    }

    void S3Handler::GetRange(const http::request<http::dynamic_body> &request, long &min, long &max, long &size) {
        if (!Core::HttpUtils::HasHeader(request, "Range")) {
            return;
        }
        std::string rangeStr = Core::HttpUtils::GetHeaderValue(request, "Range");
        std::string parts = Core::StringUtils::Split(rangeStr, '=')[1];
        min = std::stol(Core::StringUtils::Split(parts, '-')[0]);
        max = std::stol(Core::StringUtils::Split(parts, '-')[1]);
        size = max - min + 1;
        log_info << "Requested range: " << std::to_string(min) << "-" << std::to_string(max);
    }

    std::map<std::string, std::string> S3Handler::GetMetadata(const http::request<http::dynamic_body> &request) {

        std::map<std::string, std::string> metadata;
        for (const auto &meta: request.base()) {
            if (Core::StringUtils::StartsWith(meta.name_string(), "x-amz-meta")) {
                std::string name = meta.name_string().substr(sizeof("x-amz-meta-") - 1);
                metadata[name] = meta.value();
            }
        }
        log_info << "Get user metadata, size: " << metadata.size();
        return metadata;
    }

}// namespace AwsMock::Service
