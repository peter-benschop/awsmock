//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/CognitoClientCommand.h>

namespace AwsMock::Dto::Common {

    void CognitoClientCommand::FromRequest(const http::request<http::dynamic_body> &request, const std::string &awsRegion, const std::string &awsUser) {

        // From AwsMock UI
        if (Core::HttpUtils::HasHeader(request, "x-awsmock-target") && Core::HttpUtils::GetHeaderValue(request, "x-awsmock-target") == "cognito-idp") {

            this->command = CognitoCommandTypeFromString(Core::HttpUtils::GetHeaderValue(request, "x-awsmock-action"));

        } else {

            Dto::Common::UserAgent userAgent;
            userAgent.FromRequest(request);
        }

        // Basic values
        this->region = awsRegion;
        this->user = awsUser;
        this->method = request.method();
        this->url = request.target();
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->payload = Core::HttpUtils::GetBodyAsString(request);
        this->headers = Core::HttpUtils::GetHeaders(request);
        this->requestId = Core::HttpUtils::GetHeaderValue(request, "RequestId", Core::AwsUtils::CreateRequestId());
    }

    std::string CognitoClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("method", method);
            rootJson.set("region", region);
            rootJson.set("user", user);
            rootJson.set("command", Dto::Common::CognitoCommandTypeToString(command));
            rootJson.set("url", url);
            rootJson.set("contentType", contentType);
            rootJson.set("contentLength", contentLength);
            rootJson.set("payload", payload);
            rootJson.set("requestId", requestId);

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
