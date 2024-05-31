//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/UserPoolClient.h>

namespace AwsMock::Dto::Cognito {

    std::string UserPoolClient::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object UserPoolClient::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("UserPoolId", userPoolId);
            rootJson.set("ClientId", clientId);
            rootJson.set("ClientName", clientName);
            rootJson.set("ClientSecret", clientSecret);
            rootJson.set("CreationDate", Core::DateTimeUtils::ISO8601(created));
            rootJson.set("LastModified", Core::DateTimeUtils::ISO8601(lastModified));

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UserPoolClient::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UserPoolClient &o) {
        os << "UserPoolClient=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
