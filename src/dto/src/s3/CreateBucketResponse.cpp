//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateBucketResponse.h>

namespace AwsMock::Dto::S3 {

    std::string CreateBucketResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("location", location);
            rootJson.set("arn", arn);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateBucketResponse::ToXml() const {

        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = Core::XmlUtils::CreateDocument();
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = Core::XmlUtils::CreateRootNode(pDoc, "CreateBucketResult");

        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "BucketArn", arn);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "Location", location);

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    std::string CreateBucketResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateBucketResponse &r) {
        os << "CreateBucketResponse={bucket='" + r.location + "', arn='" + r.arn + "'}";
        return os;
    }

}// namespace AwsMock::Dto::S3
