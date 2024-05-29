//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/CognitoClientCommand.h>

namespace AwsMock::Dto::Common {

    void CognitoClientCommand::FromRequest(const http::request<http::string_body> &request, const std::string &awsRegion, const std::string &awsUser) {

        Dto::Common::UserAgent userAgent;
        userAgent.FromRequest(request, "cognito");

        // Basic values
        this->region = awsRegion;
        this->user = awsUser;
        this->method = request.method();
        this->url = request.target();
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->payload = request.body();
        this->headers = Core::HttpUtils::GetHeaders(request);
        this->requestId = Core::HttpUtils::GetHeaderValue(request, "RequestId");

        // Core values
        poolName = Core::HttpUtils::GetPathParameter(request.target(), 0);
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
            log_error << exc.message();
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
