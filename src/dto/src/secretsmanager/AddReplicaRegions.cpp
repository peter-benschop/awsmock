//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/AddReplicaRegions.h>

namespace AwsMock::Dto::SecretsManager {

    view_or_value<view,value> AddReplicaRegions::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document,"Region", region);
            Core::Bson::BsonUtils::SetStringValue(document,"KmsKeyId", kmsKeyId);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void AddReplicaRegions::FromJson(const view_or_value<view,value> &document) {

        try {

            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            kmsKeyId = Core::Bson::BsonUtils::GetStringValue(document, "KmsKeyId");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string AddReplicaRegions::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string AddReplicaRegions::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AddReplicaRegions &r) {
        os << "AddReplicaRegions=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SecretsManager