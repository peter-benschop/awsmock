//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/SecretsManagerClientCommand.h>

namespace AwsMock::Dto::Common {

    void SecretsManagerClientCommand::FromRequest(const HttpMethod &method, Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user) {

        Dto::Common::UserAgent userAgent;
        userAgent.FromRequest(request, "secretsmanager");

        // Basic values
        this->region = region;
        this->user = user;
        this->method = method;
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->payload = GetBodyAsString(request);
        this->url = request.getURI();

        // Command
        std::string action = request.get("X-Amz-Target");

        switch (method) {
            case HttpMethod::GET:
            case HttpMethod::PUT:
            case HttpMethod::DELETE:
                break;
            case HttpMethod::POST:
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
            case HttpMethod::UNKNOWN: {
                break;
            }
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
            rootJson.set("method", HttpMethodToString(method));
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
