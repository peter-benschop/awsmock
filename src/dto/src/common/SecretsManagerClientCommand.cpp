//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/SecretsManagerClientCommand.h>

namespace AwsMock::Dto::Common {

    void SecretsManagerClientCommand::FromRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {

        Dto::Common::UserAgent userAgent;
        userAgent.FromRequest(request);

        // Basic values
        this->region = region;
        this->user = user;
        this->method = method;
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->payload = Core::HttpUtils::GetBodyAsString1(request);
        this->url = request.target();
        this->requestId = Core::HttpUtils::GetHeaderValue(request, "RequestId", Core::AwsUtils::CreateRequestId());

        // Command
        std::string action = Core::HttpUtils::GetHeaderValue(request, "X-Amz-Target");

        switch (method) {
            case http::verb::get:
            case http::verb::put:
            case http::verb::delete_:
                break;
            case http::verb::post:
                if (Core::StringUtils::ContainsIgnoreCase(action, "CreateSecret")) {
                    command = SecretsManagerCommandType::CREATE_SECRET;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "DeleteSecret")) {
                    command = SecretsManagerCommandType::DELETE_SECRET;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "DescribeSecret")) {
                    command = SecretsManagerCommandType::DESCRIBE_SECRET;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "GetSecretValue")) {
                    command = SecretsManagerCommandType::GET_SECRET_VALUE;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "UpdateSecret")) {
                    command = SecretsManagerCommandType::UPDATE_SECRET;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "RotateSecret")) {
                    command = SecretsManagerCommandType::ROTATE_SECRET;
                } else if (Core::StringUtils::ContainsIgnoreCase(action, "ListSecrets")) {
                    command = SecretsManagerCommandType::LIST_SECRETS;
                }
                break;
        }
    }

    std::string SecretsManagerClientCommand::GetBodyAsString(Poco::Net::HTTPServerRequest &request) {
        std::stringstream sstream;
        sstream << request.stream().rdbuf();
        return sstream.str();
    }

    std::string SecretsManagerClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("method", boost::lexical_cast<std::string>(method));
            rootJson.set("command", SecretsManagerCommandTypeToString(command));
            rootJson.set("user", user);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string SecretsManagerClientCommand::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SecretsManagerClientCommand &r) {
        os << "SecretsManagerClientCommand=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Common
