//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CopyObjectResponse.h>

namespace AwsMock::Dto::S3 {

    std::string CopyObjectResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("eTag", eTag);
            rootJson.set("modified", lastModified);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CopyObjectResponse::ToXml() const {

        boost::property_tree::ptree root;
        root.add("CopyObjectResult.ETag", eTag);
        root.add("CopyObjectResult.LastModified", lastModified);
        return Core::XmlUtils::ToXmlString(root);
    }

    std::string CopyObjectResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CopyObjectResponse &r) {
        os << "CopyObjectResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
