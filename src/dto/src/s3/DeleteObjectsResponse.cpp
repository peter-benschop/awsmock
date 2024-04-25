//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/DeleteObjectsResponse.h>

namespace AwsMock::Dto::S3 {

    std::string DeleteObjectsResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("keys", Core::JsonUtils::GetJsonStringArray(keys));

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DeleteObjectsResponse::ToXml() const {

        // Root
        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = Core::XmlUtils::CreateDocument();
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = Core::XmlUtils::CreateRootNode(pDoc, "DeleteResult");

        Core::XmlUtils::CreateTextArray(pDoc, pRoot, "Deleted", "Key", keys);

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    std::string DeleteObjectsResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteObjectsResponse &r) {
        os << "DeleteObjectsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
