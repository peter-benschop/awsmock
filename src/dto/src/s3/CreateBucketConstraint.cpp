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
      throw Core::JsonException(exc.message());
    }
  }

  std::string CreateBucketConstraint::ToXml() const {

    Poco::XML::AutoPtr<Poco::XML::Document> pDoc = Core::XmlUtils::CreateDocument();
    Poco::XML::AutoPtr<Poco::XML::Element> pRoot = Core::XmlUtils::CreateRootNode(pDoc, "CreateBucketConfiguration");

    Core::XmlUtils::CreateTextNode(pDoc, pRoot, "LocationConstraint", location);

    return Core::XmlUtils::ToXmlString(pDoc);
  }

  std::string CreateBucketConstraint::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateBucketConstraint &r) {
    os << "CreateBucketConstraint=" << r.ToJson();
    return os;
  }

} // namespace AwsMock::Dto
