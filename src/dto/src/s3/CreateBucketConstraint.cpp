//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateBucketConstraint.h>

namespace AwsMock::Dto::S3 {

    std::string CreateBucketConstraint::ToJson() const {
        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "location", location);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateBucketConstraint::ToXml() const {

        boost::property_tree::ptree root;
        root.add("CreateBucketConfiguration.LocationConstraint", location);
        return Core::XmlUtils::ToXmlString(root);
    }

    std::string CreateBucketConstraint::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateBucketConstraint &r) {
        os << "CreateBucketConstraint=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
