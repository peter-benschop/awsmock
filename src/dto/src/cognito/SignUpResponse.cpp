//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/SignUpResponse.h>

namespace AwsMock::Dto::Cognito {

    void SignUpResponse::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueBool("UserConfirmed", rootObject, userConfirmed);
            Core::JsonUtils::GetJsonValueString("UserSub", rootObject, userSub);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string SignUpResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("UserConfirmed", userConfirmed);
            rootJson.set("UserSub", userSub);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string SignUpResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SignUpResponse &r) {
        os << "SignUpResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito