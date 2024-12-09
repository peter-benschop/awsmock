//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateBucketConstraint.h>

namespace AwsMock::Dto::S3 {

    std::string CreateBucketConstraint::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("location", location);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
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
