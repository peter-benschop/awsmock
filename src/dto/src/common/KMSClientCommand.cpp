//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/KMSClientCommand.h>

namespace AwsMock::Dto::Common {

    void KMSClientCommand::FromRequest(const http::request<http::string_body> &request, const std::string &awsRegion, const std::string &awsUser) {

        Dto::Common::UserAgent userAgent;
        userAgent.FromRequest(request, "kms");

        // Basic values
        this->region = awsRegion;
        this->user = awsUser;
        this->method = request.method();
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->payload = request.body();
        this->url = request.target();

        if (userAgent.clientCommand.empty()) {

            this->command = Dto::Common::KMSCommandTypeFromString(GetCommandFromHeader(request));

        } else {

            this->command = Dto::Common::KMSCommandTypeFromString(userAgent.clientCommand);
        }
    }

    std::string KMSClientCommand::GetCommandFromHeader(const http::request<http::string_body> &request) {

        std::string headerValue = Core::HttpUtils::GetHeaderValue(request, "X-Amz-Target");
        std::string cmd = Core::StringUtils::Split(headerValue, '.')[1];
        return Core::StringUtils::ToSnakeCase(cmd);
    }

    std::string KMSClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("method", boost::lexical_cast<std::string>(method));
            rootJson.set("command", KMSCommandTypeToString(command));
            rootJson.set("user", user);
            rootJson.set("contentType", contentType);
            rootJson.set("payload", payload.length() > 256 ? Core::StringUtils::SubString(payload, 0, 256) : payload);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string KMSClientCommand::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const KMSClientCommand &r) {
        os << "KMSClientCommand=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Common
