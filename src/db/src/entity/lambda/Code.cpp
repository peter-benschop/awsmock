//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/Code.h>

namespace AwsMock::Database::Entity::Lambda {

    void Code::FromDocument(std::optional<bsoncxx::document::view> mResult) {

        if (mResult.value().find("zipFile") != mResult.value().end()) {
            zipFile = Core::Bson::BsonUtils::GetStringValue(mResult, "zipFile");
        }
        if (mResult.value().find("s3Bucket") != mResult.value().end()) {
            s3Bucket = Core::Bson::BsonUtils::GetStringValue(mResult, "s3Bucket");
            s3Key = Core::Bson::BsonUtils::GetStringValue(mResult, "s3Key");
            s3ObjectVersion = Core::Bson::BsonUtils::GetStringValue(mResult, "s3ObjectVersion");
        }
    }

    view_or_value<view, value> Code::ToDocument() const {

        bsoncxx::builder::basic::document codeDoc{};
        if (!s3Bucket.empty()) {
            codeDoc.append(kvp("s3Bucket", s3Bucket));
            codeDoc.append(kvp("s3Key", s3Key));
            codeDoc.append(kvp("s3ObjectVersion", s3ObjectVersion));
        }
        if (!zipFile.empty()) {
            codeDoc.append(kvp("zipFile", zipFile));
        }
        return codeDoc.extract();
    }

    [[nodiscard]] std::string Code::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Code &t) {
        os << "Code=" << bsoncxx::to_json(t.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Lambda