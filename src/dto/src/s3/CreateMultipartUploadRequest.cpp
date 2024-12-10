//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateMultipartUploadRequest.h>

namespace AwsMock::Dto::S3 {

    std::string CreateMultipartUploadRequest::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "region", region);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "bucket", bucket);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "key", key);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "user", user);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "uploadId", uploadId);

            if (!metadata.empty()) {
                document jsonMetadata;
                for (const auto &[fst, snd]: metadata) {
                    jsonMetadata.append(kvp(fst, snd));
                }
                rootDocument.append(kvp("metadata", jsonMetadata));
            }

            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void CreateMultipartUploadRequest::FromXml(const std::string &xmlString) {

        try {

            boost::property_tree::ptree pt;
            read_xml(xmlString, pt);
            region = pt.get<std::string>("CreateBucketConfiguration.LocationConstraint");

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateMultipartUploadRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateMultipartUploadRequest &r) {
        os << "CreateMultipartUploadRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
