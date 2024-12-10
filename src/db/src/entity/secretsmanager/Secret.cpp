//
// Created by vogje01 on 24/09/2023.
//

#include <awsmock/entity/secretsmanager/Secret.h>

namespace AwsMock::Database::Entity::SecretsManager {

    view_or_value<view, value> Secret::ToDocument() const {

        view_or_value<view, value> rotationRulesDoc = make_document(
                kvp("automaticallyAfterDays", static_cast<bsoncxx::types::b_int64>(rotationRules.automaticallyAfterDays)),
                kvp("duration", rotationRules.duration),
                kvp("scheduleExpression", rotationRules.scheduleExpression));

        view_or_value<view, value> secretDoc = make_document(
                kvp("region", region),
                kvp("name", name),
                kvp("arn", arn),
                kvp("secretId", secretId),
                kvp("kmsKeyId", kmsKeyId),
                kvp("versionId", versionId),
                kvp("secretString", secretString),
                kvp("secretBinary", secretBinary),
                kvp("description", description),
                kvp("owningService", owningService),
                kvp("primaryRegion", primaryRegion),
                kvp("createdDate", static_cast<bsoncxx::types::b_int64>(createdDate)),
                kvp("deletedDate", static_cast<bsoncxx::types::b_int64>(deletedDate)),
                kvp("lastAccessedDate", static_cast<bsoncxx::types::b_int64>(lastAccessedDate)),
                kvp("lastChangedDate", static_cast<bsoncxx::types::b_int64>(lastChangedDate)),
                kvp("lastRotatedDate", static_cast<bsoncxx::types::b_int64>(lastRotatedDate)),
                kvp("nextRotatedDate", static_cast<bsoncxx::types::b_int64>(nextRotatedDate)),
                kvp("rotationEnabled", rotationEnabled),
                kvp("rotationLambdaARN", rotationLambdaARN),
                kvp("rotationRules", rotationRulesDoc),
                kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
                kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

        return secretDoc;
    }

    void Secret::FromDocument(const std::optional<view> &mResult) {

        try {
            oid = mResult.value()["_id"].get_oid().value.to_string();
            region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
            name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
            arn = bsoncxx::string::to_string(mResult.value()["arn"].get_string().value);
            secretId = bsoncxx::string::to_string(mResult.value()["secretId"].get_string().value);
            kmsKeyId = bsoncxx::string::to_string(mResult.value()["kmsKeyId"].get_string().value);
            versionId = bsoncxx::string::to_string(mResult.value()["versionId"].get_string().value);
            secretString = bsoncxx::string::to_string(mResult.value()["secretString"].get_string().value);
            secretBinary = bsoncxx::string::to_string(mResult.value()["secretBinary"].get_string().value);
            description = bsoncxx::string::to_string(mResult.value()["description"].get_string().value);
            owningService = bsoncxx::string::to_string(mResult.value()["owningService"].get_string().value);
            primaryRegion = bsoncxx::string::to_string(mResult.value()["primaryRegion"].get_string().value);
            createdDate = mResult.value()["createdDate"].get_int64().value;
            deletedDate = mResult.value()["deletedDate"].get_int64().value;
            lastAccessedDate = mResult.value()["lastAccessedDate"].get_int64().value;
            lastChangedDate = mResult.value()["lastChangedDate"].get_int64().value;
            lastRotatedDate = mResult.value()["lastRotatedDate"].get_int64().value;
            nextRotatedDate = mResult.value()["nextRotatedDate"].get_int64().value;
            rotationEnabled = mResult.value()["rotationEnabled"].get_bool().value;
            rotationLambdaARN = bsoncxx::string::to_string(mResult.value()["rotationLambdaARN"].get_string().value);
            created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
            modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

            // Get rotation rules
            if (mResult.value().find("rotationRules") != mResult.value().end()) {
                const view rotationView = mResult.value()["rotationRules"].get_document().value;
                rotationRules.automaticallyAfterDays = rotationView["automaticallyAfterDays"].get_int64().value;
                rotationRules.duration = bsoncxx::string::to_string(rotationView["duration"].get_string().value);
                rotationRules.scheduleExpression = bsoncxx::string::to_string(rotationView["scheduleExpression"].get_string().value);
            }
        } catch (const bsoncxx::exception &exc) {
            log_error << "Exception: oid: " << oid << " error: " << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Secret::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Secret &s) {
        os << "Secret=" << to_json(s.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::SecretsManager
