//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/MoveObjectResponse.h>

namespace AwsMock::Dto::S3 {

    std::string MoveObjectResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;
            root.add("MoveObjectResult.ETag", eTag);
            root.add("MoveObjectResult.LastModified", lastModified);
            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string MoveObjectResponse::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "ETag", eTag);
            Core::Bson::BsonUtils::SetStringValue(document, "LastModified", lastModified);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string MoveObjectResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const MoveObjectResponse &r) {
        os << "MoveObjectResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
