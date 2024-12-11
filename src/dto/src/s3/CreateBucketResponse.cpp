//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateBucketResponse.h>

namespace AwsMock::Dto::S3 {

    std::string CreateBucketResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "location", location);
            Core::Bson::BsonUtils::SetStringValue(document, "arn", arn);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateBucketResponse::ToXml() const {

        boost::property_tree::ptree root;
        root.add("CreateBucketResult.BucketArn", arn);
        root.add("CreateBucketResult.Location", location);
        return Core::XmlUtils::ToXmlString(root);
    }

    std::string CreateBucketResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateBucketResponse &r) {
        os << "CreateBucketResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
