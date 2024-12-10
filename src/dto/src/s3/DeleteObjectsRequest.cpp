//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/DeleteObjectsRequest.h>

namespace AwsMock::Dto::S3 {

    std::string DeleteObjectsRequest::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "bucket", bucket);

            if (!keys.empty()) {
                array keyArray;
                for (const auto &key: keys) {
                    keyArray.append(key);
                }
                document.append(kvp("keys", keyArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void DeleteObjectsRequest::FromXml(const std::string &xmlString) {

        try {
            boost::property_tree::ptree pt;
            read_xml(xmlString, pt);
            for (const auto &key: pt.get_child("Delete").data()) {
                keys.emplace_back(&key);
            }
        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteObjectsRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteObjectsRequest &r) {
        os << "DeleteObjectsRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
