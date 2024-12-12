//
// Created by vogje01 on 4/25/24.
//

#include "awsmock/dto/kms/model/ListKey.h"

namespace AwsMock::Dto::KMS {

    void ListKey::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            keyId = Core::Bson::BsonUtils::GetStringValue(document, "KeyId");
            keyArn = Core::Bson::BsonUtils::GetStringValue(document, "KeyArn");
            keyState = KeyStateFromString(Core::Bson::BsonUtils::GetStringValue(document, "KeyState"));

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> ListKey::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "KeyId", keyId);
            Core::Bson::BsonUtils::SetStringValue(document, "KeyArn", keyArn);
            Core::Bson::BsonUtils::SetStringValue(document, "KeyState", KeyStateToString(keyState));
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListKey::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string ListKey::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListKey &r) {
        os << "ListKey=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
