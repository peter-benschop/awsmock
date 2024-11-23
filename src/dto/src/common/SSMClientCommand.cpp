//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/SSMClientCommand.h>

namespace AwsMock::Dto::Common {

    void SSMClientCommand::FromRequest(const http::request<http::dynamic_body> &request, const std::string &awsRegion, const std::string &awsUser) {

        Dto::Common::UserAgent userAgent;
        userAgent.FromRequest(request);

        // Basic values
        this->region = awsRegion;
        this->user = awsUser;
        this->method = request.method();
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->payload = Core::HttpUtils::GetBodyAsString(request);
        this->url = request.target();
        this->requestId = Core::HttpUtils::GetHeaderValue(request, "RequestId", Core::AwsUtils::CreateRequestId());

        if (userAgent.clientCommand.empty()) {

            this->command = Dto::Common::SSMCommandTypeFromString(GetCommandFromHeader(request));

        } else {

            this->command = Dto::Common::SSMCommandTypeFromString(userAgent.clientCommand);
        }
    }

    std::string SSMClientCommand::GetCommandFromHeader(const http::request<http::dynamic_body> &request) {

        std::string headerValue = Core::HttpUtils::GetHeaderValue(request, "X-Amz-Target");
        std::string cmd = Core::StringUtils::Split(headerValue, '.')[1];
        return Core::StringUtils::ToSnakeCase(cmd);
    }

    std::string SSMClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("method", boost::lexical_cast<std::string>(method));
            rootJson.set("command", SSMCommandTypeToString(command));
            rootJson.set("user", user);
            rootJson.set("contentType", contentType);
            rootJson.set("payload", payload.length() > 256 ? Core::StringUtils::SubString(payload, 0, 256) : payload);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string SSMClientCommand::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SSMClientCommand &r) {
        os << "SSMClientCommand=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Common
