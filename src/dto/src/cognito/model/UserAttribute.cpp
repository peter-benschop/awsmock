//
// Created by vogje01 on 23/11/2023.
//

#include <awsmock/dto/cognito/model/UserAttribute.h>

namespace AwsMock::Dto::Cognito {

    std::string UserAttribute::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Name", name);
            rootJson.set("Value", value);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void UserAttribute::FromDocument(const std::optional<view> &document) {

        try {

            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");
            value = Core::Bson::BsonUtils::GetStringValue(document, "Value");

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UserAttribute::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UserAttribute &r) {
        os << "UserAttribute=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito
