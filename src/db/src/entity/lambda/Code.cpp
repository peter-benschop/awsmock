//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/Code.h>

namespace AwsMock::Database::Entity::Lambda {

    void Code::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        if (mResult.value().find("zipFilename") != mResult.value().end()) {
            zipFilename = bsoncxx::string::to_string(mResult.value()["zipFilename"].get_string().value);
        } else if (mResult.value().find("s3Bucket") != mResult.value().end()) {
            s3Bucket = bsoncxx::string::to_string(mResult.value()["s3Bucket"].get_string().value);
            s3Key = bsoncxx::string::to_string(mResult.value()["s3Key"].get_string().value);
            s3Version = bsoncxx::string::to_string(mResult.value()["s3Version"].get_string().value);
        }
    }

    view_or_value<view, value> Code::ToDocument() const {

        bsoncxx::builder::basic::document codeDoc{};
        if (!zipFilename.empty()) {
            codeDoc.append(kvp("zipFilename", zipFilename));
        } else if (!s3Bucket.empty()) {
            codeDoc.append(kvp("s3Bucket", s3Bucket));
            codeDoc.append(kvp("s3Key", s3Key));
            codeDoc.append(kvp("s3Version", s3Version));
        }
        return codeDoc.extract();
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