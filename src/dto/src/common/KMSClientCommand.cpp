//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/KMSClientCommand.h>

namespace AwsMock::Dto::Common {

    void KMSClientCommand::FromRequest(const HttpMethod &httpMethod, Poco::Net::HTTPServerRequest &request, const std::string &awsRegion, const std::string &awsUser) {

        // Basic values
        this->region = awsRegion;
        this->user = awsUser;
        this->method = httpMethod;
        this->contentType = Core::HttpUtils::GetHeaderValue(request, "Content-Type");
        this->payload = GetBodyAsString(request);
        this->command = Dto::Common::KMSCommandTypeFromString(GetCommandFromHeader(request));
    }

    std::string KMSClientCommand::GetBodyAsString(Poco::Net::HTTPServerRequest &request) {
        std::stringstream sstream;
        sstream << request.stream().rdbuf();
        request.stream().seekg(0, request.stream().beg);
        return sstream.str();
    }

    std::string KMSClientCommand::GetCommandFromHeader(Poco::Net::HTTPServerRequest &request) const {

        std::string cmd;
        std::string cType = request["Content-Type"];
        if (Core::StringUtils::ContainsIgnoreCase(cType, "application/x-amz-json")) {

            std::string headerValue = Core::HttpUtils::GetHeaderValue(request, "X-Amz-Target");
            cmd = Core::StringUtils::Split(headerValue, '.')[1];
        }
        return Core::StringUtils::ToSnakeCase(cmd);
    }

    std::string KMSClientCommand::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("method", HttpMethodToString(method));
            rootJson.set("command", KMSCommandTypeToString(command));
            rootJson.set("user", user);

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
