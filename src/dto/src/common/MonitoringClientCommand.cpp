//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/MonitoringClientCommand.h>

namespace AwsMock::Dto::Common {

    void MonitoringClientCommand::FromRequest(const http::request<http::dynamic_body> &request, const std::string &awsRegion, const std::string &awsUser) {

        // Basic values
        this->method = request.method();
        this->region = awsRegion;
        this->user = awsUser;
        this->url = request.target();
        this->contentType = Core::HttpUtils::GetContentType(request);
        this->contentLength = Core::HttpUtils::GetContentLength(request);
        this->payload = Core::HttpUtils::GetBodyAsString(request);
        this->headers = Core::HttpUtils::GetHeaders(request);
        this->requestId = Core::HttpUtils::GetHeaderValue(request, "RequestId", Core::AwsUtils::CreateRequestId());

        if (Core::HttpUtils::HasHeader(request, "X-AwsMock-Target")) {

            std::string target = Core::HttpUtils::GetHeaderValue(request, "X-AwsMock-Target");
            command = MonitoringCommandTypeFromString(target);
        }
    }

    std::string MonitoringClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("method", std::string(to_string(method)));
            rootJson.set("region", region);
            rootJson.set("user", user);
            rootJson.set("command", Dto::Common::MonitoringCommandTypeToString(command));
            rootJson.set("contentType", contentType);
            rootJson.set("contentLength", contentLength);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string MonitoringClientCommand::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const MonitoringClientCommand &r) {
        os << "MonitoringClientCommand=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Common
