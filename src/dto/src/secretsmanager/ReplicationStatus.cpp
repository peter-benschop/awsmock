//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/ReplicationStatus.h>

namespace AwsMock::Dto::SecretsManager {

    view_or_value<view, value> ReplicationStatus::ToDocument() const {

        /* Todo:
        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("ARN", arn);
            rootJson.set("KmsKeyId", kmsKeyId);
            rootJson.set("LastAccessedDate", lastAccessedDate);
            rootJson.set("Status", status);
            rootJson.set("StatusMessage", statusMessage);
            return rootJson;

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }*/
        return {};
    }


    void ReplicationStatus::FromDocument(const view_or_value<view, value> &document) {

        /* Todo:
        try {

            Core::JsonUtils::GetJsonValueString("Region", jsonObject, region);
            Core::JsonUtils::GetJsonValueString("ARN", jsonObject, arn);

        } catch (Poco::Exception &exc) {
            std::cerr << exc.message() << std::endl;
            throw Core::ServiceException(exc.message());
        }
        */
    }

    std::string ReplicationStatus::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string ReplicationStatus::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ReplicationStatus &r) {
        os << "ReplicationStatus=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SecretsManager