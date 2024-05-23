//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/AccountSettingsResponse.h>

namespace AwsMock::Dto::Lambda {

    std::string AccountSettingsResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("User", user);
            rootJson.set("AccountLimit", accountLimit.ToJsonObject());
            rootJson.set("AccountUsage", accountUsage.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string AccountSettingsResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AccountSettingsResponse &r) {
        os << "AccountSettingsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
