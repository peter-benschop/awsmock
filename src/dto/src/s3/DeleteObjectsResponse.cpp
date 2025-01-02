//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/DeleteObjectsResponse.h>

namespace AwsMock::Dto::S3 {

    std::string DeleteObjectsResponse::ToJson() const {

        try {

            document document;
            if (!keys.empty()) {
                array jsonArray;
                for (const auto &key: keys) {
                    jsonArray.append(key);
                }
                document.append(kvp("keys", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteObjectsResponse::ToXml() const {

        boost::property_tree::ptree root;
        boost::property_tree::ptree parent = root.add("DeleteResult", "");
        for (const auto &key: keys) {
            parent.add("Deleted.Key", key);
            parent.add("Deleted.VersionId", "");
        }
        return Core::XmlUtils::ToXmlString(root);
    }

    std::string DeleteObjectsResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteObjectsResponse &r) {
        os << "DeleteObjectsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
