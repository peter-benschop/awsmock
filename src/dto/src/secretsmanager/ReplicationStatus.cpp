//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/ReplicationStatus.h>

namespace AwsMock::Dto::SecretsManager {

    Poco::JSON::Object ReplicationStatus::ToJsonObject() const {

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
            throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    std::string ReplicationStatus::ToJson() const {

        std::ostringstream os;
        ToJsonObject().stringify(os);
        return os.str();
    }

    void ReplicationStatus::FromJson(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueString("Region", jsonObject, region);
            Core::JsonUtils::GetJsonValueString("ARN", jsonObject, arn);

        } catch (Poco::Exception &exc) {
            std::cerr << exc.message() << std::endl;
            throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    std::string ReplicationStatus::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ReplicationStatus &r) {
        os << "ReplicationStatus=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SecretsManager