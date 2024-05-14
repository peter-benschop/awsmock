//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/AddReplicaRegions.h>

namespace AwsMock::Dto::SecretsManager {

    Poco::JSON::Object AddReplicaRegions::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("KmsKeyId", kmsKeyId);
            return rootJson;

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string AddReplicaRegions::ToJson() const {

        std::ostringstream os;
        ToJsonObject().stringify(os);
        return os.str();
    }

    void AddReplicaRegions::FromJson(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueString("Region", jsonObject, region);
            Core::JsonUtils::GetJsonValueString("KmsKeyId", jsonObject, kmsKeyId);

        } catch (Poco::Exception &exc) {
            std::cerr << exc.message() << std::endl;
            throw Core::ServiceException(exc.message());
        }
    }

    std::string AddReplicaRegions::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AddReplicaRegions &r) {
        os << "AddReplicaRegions=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SecretsManager