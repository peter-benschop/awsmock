//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/model/Key.h>

namespace AwsMock::Dto::KMS {

    void Key::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            keyId = Core::Bson::BsonUtils::GetStringValue(document, "KeyId");
            keySpec = KeySpecFromString(Core::Bson::BsonUtils::GetStringValue(document, "KeySpec"));
            keyUsage = KeyUsageFromString(Core::Bson::BsonUtils::GetStringValue(document, "KeyUsage"));
            keyState = KeyStateFromString(Core::Bson::BsonUtils::GetStringValue(document, "KeyState"));
            description = Core::Bson::BsonUtils::GetStringValue(document, "Description");
            arn = Core::Bson::BsonUtils::GetStringValue(document, "Arn");
            creationDate = Core::Bson::BsonUtils::GetLongValue(document, "CreationDate");
            multiRegion = Core::Bson::BsonUtils::GetBoolValue(document, "MultiRegion");
            enabled = Core::Bson::BsonUtils::GetBoolValue(document, "Enabled");
            origin = OriginFromString(Core::Bson::BsonUtils::GetStringValue(document, "Origin"));

            // Grant tokens
            if (document.view().find("EncryptionAlgorithms") != document.view().end()) {
                for (const bsoncxx::array::view jsonArray = document.view()["EncryptionAlgorithms"].get_array().value; const auto &element: jsonArray) {
                    encryptionAlgorithms.emplace_back(EncryptionAlgorithmsFromString(std::string(element.get_string().value)));
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> Key::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "KeyId", keyId);
            Core::Bson::BsonUtils::SetStringValue(document, "KeySpec", KeySpecToString(keySpec));
            Core::Bson::BsonUtils::SetStringValue(document, "KeyUsage", KeyUsageToString(keyUsage));
            Core::Bson::BsonUtils::SetStringValue(document, "KeyState", KeyStateToString(keyState));
            Core::Bson::BsonUtils::SetStringValue(document, "Arn", arn);
            Core::Bson::BsonUtils::SetLongValue(document, "CreationDate", creationDate);
            Core::Bson::BsonUtils::SetLongValue(document, "DeletionDate", deletionDate);
            Core::Bson::BsonUtils::SetBoolValue(document, "MultiRegion", multiRegion);
            Core::Bson::BsonUtils::SetStringValue(document, "Origin", OriginToString(origin));

            if (!encryptionAlgorithms.empty()) {
                array jsonArray;
                for (const auto &element: encryptionAlgorithms) {
                    jsonArray.append(EncryptionAlgorithmsToString(element));
                }
                document.append(kvp("EncryptionAlgorithms", jsonArray));
            }
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Key::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Key::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Key &r) {
        os << "Key=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
