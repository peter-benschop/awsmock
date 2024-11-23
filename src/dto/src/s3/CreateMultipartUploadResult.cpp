//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateMultipartUploadResult.h>

namespace AwsMock::Dto::S3 {

    std::string CreateMultipartUploadResult::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("bucket", bucket);
            rootJson.set("key", key);
            rootJson.set("uploadId", uploadId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }


    std::string CreateMultipartUploadResult::ToXml() const {

        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = Core::XmlUtils::CreateDocument();
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = Core::XmlUtils::CreateRootNode(pDoc, "InitiateMultipartUploadResult");

        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "Bucket", bucket);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "Key", key);
        Core::XmlUtils::CreateTextNode(pDoc, pRoot, "UploadId", uploadId);

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    void CreateMultipartUploadResult::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("Bucket", rootObject, bucket);
            Core::JsonUtils::GetJsonValueString("Key", rootObject, key);
            Core::JsonUtils::GetJsonValueString("UploadId", rootObject, uploadId);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    /**
   * Converts the DTO to a string representation.
   *
   * @return DTO as string for logging.
   */
    std::string CreateMultipartUploadResult::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    /**
   * Stream provider.
   *
   * @return output stream
   */
    std::ostream &operator<<(std::ostream &os, const CreateMultipartUploadResult &r) {
        os << "CreateMultipartUploadResult=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
