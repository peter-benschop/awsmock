//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CopyObjectResponse.h>

namespace AwsMock::Dto::S3 {

    std::string CopyObjectResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("eTag", eTag);
            rootJson.set("lastModified", lastModified);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    std::string CopyObjectResponse::ToXml() const {

        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = Core::XmlUtils::CreateDocument();
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = Core::XmlUtils::CreateRootNode(pDoc, "CopyObjectResult");

        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "ETag", eTag);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "LastModified", lastModified);

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    std::string CopyObjectResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CopyObjectResponse &r) {
        os << "CopyObjectResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
