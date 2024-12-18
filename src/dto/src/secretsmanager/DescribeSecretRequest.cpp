//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/DescribeSecretRequest.h>

namespace AwsMock::Dto::SecretsManager {

    std::string DescribeSecretRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "SecretId", secretId);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void DescribeSecretRequest::FromJson(const std::string &jsonString) {

        try {

            // Queue
            const value document = bsoncxx::from_json(jsonString);
            secretId = Core::Bson::BsonUtils::GetStringValue(document, "SecretId");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DescribeSecretRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeSecretRequest &r) {
        os << "DescribeSecretRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
