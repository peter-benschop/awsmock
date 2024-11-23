//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/entity/s3/BucketEncryption.h>

namespace AwsMock::Database::Entity::S3 {

    view_or_value<view, value> BucketEncryption::ToDocument() const {

        try {

            view_or_value<view, value> notificationDoc = make_document(
                    kvp("sseAlgorithm", sseAlgorithm),
                    kvp("kmsKeyId", kmsKeyId));
            return notificationDoc;

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::DatabaseException(exc.what());
        }
    }

    void BucketEncryption::FromDocument(const mongocxx::stdx::optional<view> &mResult) {

        try {

            sseAlgorithm = mResult.value()["sseAlgorithm"].get_string().value;
            kmsKeyId = mResult.value()["kmsKeyId"].get_string();

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::DatabaseException(exc.what());
        }
    }

    Poco::JSON::Object BucketEncryption::ToJsonObject() const {
        Poco::JSON::Object jsonObject;
        jsonObject.set("sseAlgorithm", sseAlgorithm);
        jsonObject.set("kmsKeyId", kmsKeyId);
        return jsonObject;
    }

    void BucketEncryption::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        Core::JsonUtils::GetJsonValueString("sseAlgorithm", jsonObject, sseAlgorithm);
        Core::JsonUtils::GetJsonValueString("kmsKeyId", jsonObject, kmsKeyId);
    }

    std::string BucketEncryption::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const BucketEncryption &n) {
        os << "BucketEncryption=" << to_json(n.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::S3
