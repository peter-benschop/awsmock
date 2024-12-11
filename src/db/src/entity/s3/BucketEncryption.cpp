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

    void BucketEncryption::FromDocument(const std::optional<view> &mResult) {
        try {
            sseAlgorithm = Core::Bson::BsonUtils::GetStringValue(mResult.value()["sseAlgorithm"]);
            kmsKeyId = Core::Bson::BsonUtils::GetStringValue(mResult.value()["kmsKeyId"]);
        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::DatabaseException(exc.what());
        }
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
