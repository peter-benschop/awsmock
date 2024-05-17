//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/CognitoClientCommand.h>

namespace AwsMock::Dto::Common {

    void CognitoClientCommand::FromRequest(const HttpMethod &httpMethod, Poco::Net::HTTPServerRequest &request, const std::string &awsRegion, const std::string &awsUser) {

        Dto::Common::UserAgent userAgent;
        userAgent.FromRequest(request, "s3");

        // Basic values
        this->region = awsRegion;
        this->user = awsUser;
        this->method = httpMethod;
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->url = request.getURI();

        // Core values
        poolName = Core::HttpUtils::GetPathParameter(request.getURI(), 0);

        if (!userAgent.clientCommand.empty()) {

            GetCommandFromUserAgent(method, userAgent);

        } else {

            /*            switch (method) {

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
            }*/
        }
    }

    void CognitoClientCommand::GetCommandFromUserAgent(const HttpMethod &httpMethod, const UserAgent &userAgent) {
        /*if (userAgent.clientCommand == "mb") {
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
        } else if (userAgent.clientModule == "command/s3api" && userAgent.clientCommand == "put-bucket-notification-configuration") {
            command = S3CommandType::PUT_BUCKET_NOTIFICATION_CONFIGURATION;
        } else if (userAgent.clientModule == "command/s3api" && userAgent.clientCommand == "put-bucket-encryption") {
            command = S3CommandType::PUT_BUCKET_ENCRYPTION;
        } else if (userAgent.clientModule == "command/s3api" && userAgent.clientCommand == "list-object-versions") {
            command = S3CommandType::LIST_OBJECT_VERSIONS;
        }*/
    }

    std::string CognitoClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("method", method);
            rootJson.set("region", region);
            rootJson.set("user", user);
            rootJson.set("command", Dto::Common::CognitoCommandTypeToString(command));

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    std::string CognitoClientCommand::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CognitoClientCommand &r) {
        os << "CognitoClientCommand=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Common
