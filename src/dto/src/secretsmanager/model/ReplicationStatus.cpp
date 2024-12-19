//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/model/ReplicationStatus.h>

namespace AwsMock::Dto::SecretsManager {

    view_or_value<view, value> ReplicationStatus::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "ARN", arn);
            Core::Bson::BsonUtils::SetStringValue(document, "KmsKeyId", kmsKeyId);
            Core::Bson::BsonUtils::SetLongValue(document, "LastAccessedDate", lastAccessedDate);
            Core::Bson::BsonUtils::SetStringValue(document, "Status", status);
            Core::Bson::BsonUtils::SetStringValue(document, "StatusMessage", statusMessage);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }


    void ReplicationStatus::FromDocument(const view_or_value<view, value> &document) {

        try {

            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            arn = Core::Bson::BsonUtils::GetStringValue(document, "ARN");
            kmsKeyId = Core::Bson::BsonUtils::GetStringValue(document, "KmsKeyId");
            lastAccessedDate = Core::Bson::BsonUtils::GetLongValue(document, "LastAccessedDate");
            status = Core::Bson::BsonUtils::GetStringValue(document, "Status");
            statusMessage = Core::Bson::BsonUtils::GetStringValue(document, "StatusMessage");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ReplicationStatus::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string ReplicationStatus::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ReplicationStatus &r) {
        os << "ReplicationStatus=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SecretsManager