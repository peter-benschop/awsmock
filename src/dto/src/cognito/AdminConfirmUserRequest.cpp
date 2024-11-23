//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/AdminConfirmUserRequest.h>

namespace AwsMock::Dto::Cognito {

    void AdminConfirmUserRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("Username", rootObject, userName);
            Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string AdminConfirmUserRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("Username", userName);
            rootJson.set("UserPoolId", userPoolId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string AdminConfirmUserRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AdminConfirmUserRequest &r) {
        os << "AdminConfirmUserRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito