//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/Group.h>

namespace AwsMock::Dto::Cognito {

    std::string Group::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object Group::ToJsonObject() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("GroupName", groupName);
            rootJson.set("UserPoolId", userPoolId);
            rootJson.set("Description", description);
            rootJson.set("Precedence", precedence);
            rootJson.set("CreationDate", Core::DateTimeUtils::ISO8601(created));
            rootJson.set("LastModified", Core::DateTimeUtils::ISO8601(modified));
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Group::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Group &o) {
        os << "Group=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
