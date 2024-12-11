//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/model/Code.h>

namespace AwsMock::Dto::Lambda {

    void Code::FromDocument(const view_or_value<view, value> &document) {

        try {

            s3Bucket = Core::Bson::BsonUtils::GetStringValue(document, "S3Bucket");
            s3Key = Core::Bson::BsonUtils::GetStringValue(document, "S3Key");
            s3ObjectVersion = Core::Bson::BsonUtils::GetStringValue(document, "S3ObjectVersion");
            imageUri = Core::Bson::BsonUtils::GetStringValue(document, "ImageUri");
            zipFile = Core::Bson::BsonUtils::GetStringValue(document, "ZipFile");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Code::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    view_or_value<view, value> Code::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "ZipFile", zipFile);
            Core::Bson::BsonUtils::SetStringValue(document, "S3Bucket", s3Bucket);
            Core::Bson::BsonUtils::SetStringValue(document, "S3Key", s3Key);
            Core::Bson::BsonUtils::SetStringValue(document, "S3ObjectVersion", s3ObjectVersion);
            Core::Bson::BsonUtils::SetStringValue(document, "ImageUri", imageUri);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Code::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Code &r) {
        os << "Code=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
