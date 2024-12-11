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

            UserAgent userAgent;
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

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "method", boost::lexical_cast<std::string>(method));
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "command", CognitoCommandTypeToString(command));
            Core::Bson::BsonUtils::SetStringValue(document, "url", url);
            Core::Bson::BsonUtils::SetStringValue(document, "contentType", contentType);
            Core::Bson::BsonUtils::SetIntValue(document, "contentLength", contentLength);
            Core::Bson::BsonUtils::SetStringValue(document, "payload", payload);
            Core::Bson::BsonUtils::SetStringValue(document, "requestId", requestId);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CognitoClientCommand::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CognitoClientCommand &r) {
        os << "CognitoClientCommand=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Common
