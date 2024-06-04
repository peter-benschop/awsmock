//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/Code.h>

namespace AwsMock::Database::Entity::Lambda {

    void Code::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        if (mResult.value().find("zipFile") != mResult.value().end()) {
            zipFile = bsoncxx::string::to_string(mResult.value()["zipFile"].get_string().value);
        }
        if (mResult.value().find("s3Bucket") != mResult.value().end()) {
            s3Bucket = bsoncxx::string::to_string(mResult.value()["s3Bucket"].get_string().value);
            s3Key = bsoncxx::string::to_string(mResult.value()["s3Key"].get_string().value);
            s3ObjectVersion = bsoncxx::string::to_string(mResult.value()["s3ObjectVersion"].get_string().value);
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

    Poco::JSON::Object Code::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        if (!zipFile.empty()) {
            jsonObject.set("zipFile", zipFile);
        }
        if (!s3Bucket.empty()) {
            jsonObject.set("s3Bucket", s3Bucket);
            jsonObject.set("s3Key", s3Key);
            jsonObject.set("s3ObjectVersion", s3ObjectVersion);
        }
        return jsonObject;
    }

    [[nodiscard]] std::string Code::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Code &t) {
        os << "Code=" << bsoncxx::to_json(t.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Lambda