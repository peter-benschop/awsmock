//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/CopyObjectResponse.h>

namespace AwsMock::Dto::S3 {

    std::string CopyObjectResponse::ToJson() const {


        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "eTag", eTag);
            Core::Bson::BsonUtils::SetDateValue(document, "modified", modified);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CopyObjectResponse::ToXml() const {

        boost::property_tree::ptree root;
        root.add("CopyObjectResult.ETag", eTag);
        root.add("CopyObjectResult.LastModified", Core::DateTimeUtils::ToISO8601(modified));
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
