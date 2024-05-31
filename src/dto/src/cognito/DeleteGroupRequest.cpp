//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/DeleteGroupRequest.h>

namespace AwsMock::Dto::Cognito {

    void DeleteGroupRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("GroupName", rootObject, groupName);
            Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DeleteGroupRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("GroupName", groupName);
            rootJson.set("UserPoolId", userPoolId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DeleteGroupRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteGroupRequest &r) {
        os << "DeleteGroupRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito