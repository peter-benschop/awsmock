//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CreateBucketRequest.h>

namespace AwsMock::Dto::S3 {

    std::string CreateBucketRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("name", name);
            rootJson.set("owner", owner);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void CreateBucketRequest::FromXml(const std::string &xmlString) {

        Poco::XML::DOMParser parser;
        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

        Poco::XML::Node *node = pDoc->getNodeByPath("/CreateBucketConfiguration/LocationConstraint");
        region = node->innerText();
    }

    std::string CreateBucketRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateBucketRequest &r) {
        os << "CreateBucketRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
