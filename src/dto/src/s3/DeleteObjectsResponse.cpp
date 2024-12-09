//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/DeleteObjectsResponse.h>
#include <mongocxx/options/gridfs/bucket.hpp>

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

        boost::property_tree::ptree root;
        for (const auto &key: keys) {
            root.add("DeleteResult.Key", key);
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
