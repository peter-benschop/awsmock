//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/UserContextData.h>

namespace AwsMock::Dto::Cognito {

    std::string UserContextData::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object UserContextData::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("EncodedData", encodedData);
            rootJson.set("IpAddress", ipAddress);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UserContextData::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UserContextData &o) {
        os << "UserContextData=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
