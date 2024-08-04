//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/S3ClientCommand.h>

namespace AwsMock::Dto::Common {

    void S3ClientCommand::FromRequest(const http::request<http::dynamic_body> &request, const std::string &awsRegion, const std::string &awsUser) {

        Dto::Common::UserAgent userAgent;
        userAgent.FromRequest(request);

        // Basic values
        this->region = awsRegion;
        this->user = awsUser;
        this->method = request.method();
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->url = request.target();
        this->requestId = Core::HttpUtils::GetHeaderValue(request, "RequestId", Core::AwsUtils::CreateRequestId());

        // Core values
        bucket = Core::AwsUtils::GetS3BucketName(request);
        key = Core::AwsUtils::GetS3ObjectKey(request);

        // Multipart uploads/downloads
        uploads = Core::HttpUtils::HasQueryParameter(request.target(), "uploads");
        uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "uploadId");
        uploadPartCopy = Core::HttpUtils::HasHeader(request, "x-amz-copy-source") && Core::HttpUtils::HasHeader(request, "x-amz-copy-source-range");
        partNumber = Core::HttpUtils::HasQueryParameter(request.target(), "partNumber");
        rangeRequest = Core::HttpUtils::HasHeader(request, "Range");
        multipartRequest = uploads || !uploadId.empty() || partNumber;

        notificationRequest = Core::HttpUtils::HasQueryParameter(request.target(), "notification");
        versionRequest = Core::HttpUtils::HasQueryParameter(request.target(), "versioning");
        copyRequest = Core::HttpUtils::HasHeader(request, "x-amz-copy-source");
        encryptionRequest = Core::HttpUtils::HasQueryParameter(request.target(), "encryption");

        if (!userAgent.clientCommand.empty()) {

            GetCommandFromUserAgent(method, userAgent);

        } else {

            switch (method) {

                case http::verb::get:
                    if (bucket.empty() && key.empty()) {
                        command = S3CommandType::LIST_BUCKETS;
                    } else if (!bucket.empty() && key.empty()) {
                        if (Core::HttpUtils::HasQueryParameter(request.target(), "versions")) {
                            prefix = Core::HttpUtils::GetQueryParameterValueByName(request.target(), "prefix");
                            command = S3CommandType::LIST_OBJECT_VERSIONS;
                        } else {
                            command = S3CommandType::LIST_OBJECTS;
                        }
                    } else if (rangeRequest && !partNumber) {
                        command = S3CommandType::GET_OBJECT_RANGE;
                    } else {
                        command = S3CommandType::GET_OBJECT;
                    }
                    break;

                case http::verb::put:
                    if (multipartRequest) {
                        if (uploadPartCopy) {
                            command = S3CommandType::UPLOAD_PART_COPY;
                        } else {
                            command = S3CommandType::UPLOAD_PART;
                        }
                    } else if (encryptionRequest) {
                        command = S3CommandType::PUT_BUCKET_ENCRYPTION;
                    } else if (notificationRequest) {
                        command = S3CommandType::BUCKET_NOTIFICATION;
                    } else if (!bucket.empty() && key.empty()) {
                        command = S3CommandType::CREATE_BUCKET;
                    } else if (!bucket.empty() && !key.empty()) {
                        command = S3CommandType::PUT_OBJECT;
                    }
                    break;

                case http::verb::post:
                    if (!bucket.empty() && !key.empty()) {
                        if (uploads) {
                            command = S3CommandType::CREATE_MULTIPART_UPLOAD;
                        } else if (multipartRequest) {
                            command = S3CommandType::COMPLETE_MULTIPART_UPLOAD;
                        }
                    } else if (!bucket.empty()) {
                        command = S3CommandType::DELETE_OBJECTS;
                    }
                    break;

                case http::verb::delete_:
                    if (multipartRequest) {
                        command = S3CommandType::ABORT_MULTIPART_UPLOAD;
                    } else if (!bucket.empty() && key.empty()) {
                        command = S3CommandType::DELETE_BUCKET;
                    } else if (!bucket.empty() && !key.empty()) {
                        command = S3CommandType::DELETE_OBJECT;
                    }
                    break;

                case http::verb::head:
                case http::verb::unknown:
                case http::verb::connect:
                case http::verb::options:
                case http::verb::trace:
                case http::verb::copy:
                case http::verb::lock:
                case http::verb::mkcol:
                case http::verb::move:
                case http::verb::propfind:
                case http::verb::proppatch:
                case http::verb::search:
                case http::verb::unlock:
                case http::verb::bind:
                case http::verb::rebind:
                case http::verb::unbind:
                case http::verb::acl:
                case http::verb::report:
                case http::verb::mkactivity:
                case http::verb::checkout:
                case http::verb::merge:
                case http::verb::msearch:
                case http::verb::notify:
                case http::verb::subscribe:
                case http::verb::unsubscribe:
                case http::verb::patch:
                case http::verb::purge:
                case http::verb::mkcalendar:
                case http::verb::link:
                case http::verb::unlink:
                    break;
            }
        }
        log_trace << "Client command: " << ToString();
    }

    void S3ClientCommand::GetCommandFromUserAgent(const http::verb &httpMethod, const UserAgent &userAgent) {
        if (userAgent.clientCommand == "mb") {
            command = S3CommandType::CREATE_BUCKET;
        } else if (userAgent.clientCommand == "ls") {
            if (bucket.empty() && key.empty()) {
                command = S3CommandType::LIST_BUCKETS;
            } else if (!bucket.empty()) {
                command = S3CommandType::LIST_OBJECTS;
            }
        } else if (userAgent.clientCommand == "cp") {
            if (httpMethod == http::verb::put) {
                if (multipartRequest) {
                    command = S3CommandType::UPLOAD_PART;
                } else {
                    command = S3CommandType::PUT_OBJECT;
                }
            } else if (httpMethod == http::verb::get) {
                command = S3CommandType::GET_OBJECT;
            } else if (httpMethod == http::verb::post) {
                if (multipartRequest && uploadId.empty()) {
                    command = S3CommandType::CREATE_MULTIPART_UPLOAD;
                } else {
                    command = S3CommandType::COMPLETE_MULTIPART_UPLOAD;
                }
            }
        } else if (userAgent.clientCommand == "mv") {
            command = S3CommandType::MOVE_OBJECT;
        } else if (userAgent.clientCommand == "rb") {
            command = S3CommandType::DELETE_BUCKET;
        } else if (userAgent.clientCommand == "rm") {
            command = S3CommandType::DELETE_OBJECT;
        } else if (userAgent.clientModule == "s3api" && userAgent.clientCommand == "create-multipart-upload") {
            command = S3CommandType::CREATE_MULTIPART_UPLOAD;
        } else if (userAgent.clientModule == "s3api" && userAgent.clientCommand == "upload-part") {
            command = S3CommandType::UPLOAD_PART;
        } else if (userAgent.clientModule == "s3api" && userAgent.clientCommand == "complete-multipart-upload") {
            command = S3CommandType::COMPLETE_MULTIPART_UPLOAD;
        } else if (userAgent.clientModule == "s3api" && userAgent.clientCommand == "put-bucket-notification-configuration") {
            command = S3CommandType::PUT_BUCKET_NOTIFICATION_CONFIGURATION;
        } else if (userAgent.clientModule == "s3api" && userAgent.clientCommand == "put-bucket-encryption") {
            command = S3CommandType::PUT_BUCKET_ENCRYPTION;
        } else if (userAgent.clientModule == "s3api" && userAgent.clientCommand == "list-object-versions") {
            command = S3CommandType::LIST_OBJECT_VERSIONS;
        }
    }

    std::string S3ClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("method", std::string(to_string(method)));
            rootJson.set("region", region);
            rootJson.set("user", user);
            rootJson.set("command", Dto::Common::S3CommandTypeToString(command));
            rootJson.set("bucket", bucket);
            rootJson.set("key", key);
            rootJson.set("prefix", prefix);
            rootJson.set("contentType", contentType);
            rootJson.set("contentLength", contentLength);
            rootJson.set("versionRequest", versionRequest);
            rootJson.set("notificationRequest", notificationRequest);
            rootJson.set("multipartRequest", multipartRequest);
            rootJson.set("uploads", uploads);
            rootJson.set("partNumber", partNumber);
            rootJson.set("copyRequest", copyRequest);
            rootJson.set("uploadId", uploadId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string S3ClientCommand::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const S3ClientCommand &r) {
        os << "S3ClientCommand=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Common
