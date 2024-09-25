//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/GlobalSignOutRequest.h>

namespace AwsMock::Dto::Cognito {

    void GlobalSignOutRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("AccessToken", rootObject, accessToken);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GlobalSignOutRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("AccessToken", accessToken);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GlobalSignOutRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GlobalSignOutRequest &r) {
        os << "GlobalSignOutRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito