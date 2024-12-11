//
// Created by vogje01 on 23/11/2023.
//

#include <awsmock/dto/cognito/model/UserAttribute.h>

namespace AwsMock::Dto::Cognito {

    std::string UserAttribute::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "Value", value);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
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
