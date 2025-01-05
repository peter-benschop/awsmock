//
// Created by vogje01 on 13/10/2023.
//

#include <awsmock/dto/s3/PutBucketVersioningRequest.h>

namespace AwsMock::Dto::S3 {

    void PutBucketVersioningRequest::FromXml(const std::string &xmlString) {

        try {

            boost::property_tree::ptree pt;
            Core::XmlUtils::ReadXml(xmlString, &pt);
            status = pt.get<std::string>("VersioningConfiguration.Status");

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string PutBucketVersioningRequest::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "Bucket", bucket);
            Core::Bson::BsonUtils::SetStringValue(document, "Owner", owner);
            Core::Bson::BsonUtils::SetStringValue(document, "Status", status);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }
    std::string PutBucketVersioningRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutBucketVersioningRequest &r) {
        os << "PutBucketVersioningRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
