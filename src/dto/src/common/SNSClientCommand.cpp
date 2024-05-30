//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/SNSClientCommand.h>

namespace AwsMock::Dto::Common {

    void SNSClientCommand::FromRequest(const http::request<http::dynamic_body> &request, const std::string &awsRegion, const std::string &awsUser) {

        Dto::Common::UserAgent userAgent;
        userAgent.FromRequest(request);

        // Basic values
        this->region = awsRegion;
        this->user = awsUser;
        this->method = request.method();
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->payload = Core::HttpUtils::GetBodyAsString1(request);
        this->url = request.target();

        if (userAgent.clientCommand.empty()) {

            this->command = Dto::Common::SNSCommandTypeFromString(GetCommandFromHeader(request));

        } else {

            this->command = Dto::Common::SNSCommandTypeFromString(userAgent.clientCommand);
        }
    }

    std::string SNSClientCommand::GetCommandFromHeader(const http::request<http::dynamic_body> &request) const {

        std::string cmd;
        std::string cType = request["Content-Type"];
        if (Core::StringUtils::ContainsIgnoreCase(cType, "application/x-www-form-urlencoded")) {

            cmd = Core::HttpUtils::GetQueryParameterValueByName(payload, "Action");

        } else if (Core::StringUtils::ContainsIgnoreCase(cType, "application/x-amz-json-1.0")) {

            std::string headerValue = request["X-Amz-Target"];
            cmd = Core::StringUtils::Split(headerValue, '.')[1];
        }
        return Core::StringUtils::ToSnakeCase(cmd);
    }

    std::string SNSClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("method", boost::lexical_cast<std::string>(method));
            rootJson.set("command", SNSCommandTypeToString(command));
            rootJson.set("user", user);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string SNSClientCommand::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SNSClientCommand &r) {
        os << "SNSClientCommand=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Common
