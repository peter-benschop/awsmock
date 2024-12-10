//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/EncryptResponse.h>

namespace AwsMock::Dto::KMS {

    void EncryptResponse::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            std::string tmpStr;
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("KeyId", rootObject, keyId);
            Core::JsonUtils::GetJsonValueString("CiphertextBlob", rootObject, ciphertext);
            Core::JsonUtils::GetJsonValueString("EncryptionAlgorithm", rootObject, tmpStr);
            if (!tmpStr.empty()) {
                encryptionAlgorithm = Dto::KMS::EncryptionAlgorithmsFromString(tmpStr);
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string EncryptResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("KeyId", keyId);
            rootJson.set("CiphertextBlob", ciphertext);
            rootJson.set("EncryptionAlgorithm", Dto::KMS::EncryptionAlgorithmsToString(encryptionAlgorithm));

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string EncryptResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const EncryptResponse &r) {
        os << "EncryptResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
