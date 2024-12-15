//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateMultipartUploadResult.h>

namespace AwsMock::Dto::S3 {

    std::string CreateMultipartUploadResult::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "bucket", bucket);
            Core::Bson::BsonUtils::SetStringValue(document, "key", key);
            Core::Bson::BsonUtils::SetStringValue(document, "uploadId", uploadId);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void CreateMultipartUploadResult::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            bucket = Core::Bson::BsonUtils::GetStringValue(document, "Bucket");
            key = Core::Bson::BsonUtils::GetStringValue(document, "Key");
            uploadId = Core::Bson::BsonUtils::GetStringValue(document, "UploadId");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }


    std::string CreateMultipartUploadResult::ToXml() const {

        boost::property_tree::ptree root;
        root.add("InitiateMultipartUploadResult.Bucket", bucket);
        root.add("InitiateMultipartUploadResult.Key", key);
        root.add("InitiateMultipartUploadResult.UploadId", uploadId);
        return Core::XmlUtils::ToXmlString(root);
    }

    std::string CreateMultipartUploadResult::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateMultipartUploadResult &r) {
        os << "CreateMultipartUploadResult=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
