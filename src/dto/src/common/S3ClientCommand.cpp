//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/S3ClientCommand.h>

namespace AwsMock::Dto::Common {

    void S3ClientCommand::FromRequest(const HttpMethod &method, Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user) {

        Dto::Common::UserAgent userAgent;
        userAgent.FromRequest(request, "s3");

        // Basic values
        this->region = region;
        this->user = user;
        this->method = method;

        // Core values
        bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
        key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);

        // Qualifiers
        url = request.getURI();
        multipartRequest = Core::HttpUtils::HasQueryParameter(request.getURI(), "uploads") || Core::HttpUtils::HasQueryParameter(request.getURI(), "uploadId") || Core::HttpUtils::HasQueryParameter(request.getURI(), "partNumber");
        uploads = Core::HttpUtils::HasQueryParameter(request.getURI(), "uploads");
        partNumber = Core::HttpUtils::HasQueryParameter(request.getURI(), "partNumber");
        notificationRequest = Core::HttpUtils::HasQueryParameter(request.getURI(), "notification");
        versionRequest = Core::HttpUtils::HasQueryParameter(request.getURI(), "versioning");
        copyRequest = request.has("x-amz-copy-source");
        uploadId = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "uploadId");

        if (!userAgent.clientCommand.empty()) {

            GetCommandFromUserAgent(method, userAgent);

        } else {

            switch (method) {

                case HttpMethod::GET:
                    if (bucket.empty() && key.empty()) {
                        command = S3CommandType::LIST_BUCKETS;
                    } else if (!bucket.empty() && key.empty()) {
                        if (Core::HttpUtils::HasQueryParameter(request.getURI(), "versions")) {
                            prefix = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "prefix");
                            command = S3CommandType::LIST_OBJECT_VERSIONS;
                        } else {
                            command = S3CommandType::LIST_OBJECTS;
                        }
                    } else {
                        command = S3CommandType::GET_OBJECT;
                    }
                    break;

                case HttpMethod::PUT:
                    if (multipartRequest) {
                        command = S3CommandType::UPLOAD_PART;
                    } else if (!bucket.empty() && key.empty()) {
                        command = S3CommandType::CREATE_BUCKET;
                    } else if (!bucket.empty() && !key.empty()) {
                        command = S3CommandType::PUT_OBJECT;
                    }
                    break;

                case HttpMethod::POST:
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

                case HttpMethod::DELETE:
                    if (multipartRequest) {
                        command = S3CommandType::ABORT_MULTIPART_UPLOAD;
                    } else if (!bucket.empty() && key.empty()) {
                        command = S3CommandType::DELETE_BUCKET;
                    } else if (!bucket.empty() && !key.empty()) {
                        command = S3CommandType::DELETE_OBJECT;
                    }
                    break;

                case HttpMethod::UNKNOWN: {
                    break;
                }
            }
        }
        //log_debug << ToJson();
    }

    void S3ClientCommand::GetCommandFromUserAgent(const HttpMethod &httpMethod, const UserAgent &userAgent) {
        if (userAgent.clientCommand == "mb") {
            command = S3CommandType::CREATE_BUCKET;
        } else if (userAgent.clientCommand == "ls") {
            if (bucket.empty() && key.empty()) {
                command = S3CommandType::LIST_BUCKETS;
            } else if (!bucket.empty()) {
                command = S3CommandType::LIST_OBJECTS;
            }
        } else if (userAgent.clientCommand == "cp") {
            if (httpMethod == HttpMethod::PUT) {
                if (multipartRequest) {
                    command = S3CommandType::UPLOAD_PART;
                } else {
                    command = S3CommandType::PUT_OBJECT;
                }
            } else if (httpMethod == HttpMethod::GET) {
                command = S3CommandType::GET_OBJECT;
            } else if (httpMethod == HttpMethod::POST) {
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
        } else if (userAgent.clientModule == "command/s3api" && userAgent.clientCommand == "create-multipart-upload") {
            command = S3CommandType::CREATE_MULTIPART_UPLOAD;
        } else if (userAgent.clientModule == "command/s3api" && userAgent.clientCommand == "upload-part") {
            command = S3CommandType::UPLOAD_PART;
        } else if (userAgent.clientModule == "command/s3api" && userAgent.clientCommand == "complete-multipart-upload") {
            command = S3CommandType::COMPLETE_MULTIPART_UPLOAD;
        }
    }

    std::string S3ClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("method", method);
            rootJson.set("region", region);
            rootJson.set("user", user);
            rootJson.set("command", Dto::Common::S3CommandTypeToString(command));
            rootJson.set("bucket", bucket);
            rootJson.set("key", key);
            rootJson.set("prefix", prefix);
            rootJson.set("versionRequest", versionRequest);
            rootJson.set("notificationRequest", notificationRequest);
            rootJson.set("multipartRequest", multipartRequest);
            rootJson.set("uploads", uploads);
            rootJson.set("partNumber", partNumber);
            rootJson.set("copyRequest", copyRequest);
            rootJson.set("uploadId", uploadId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
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
