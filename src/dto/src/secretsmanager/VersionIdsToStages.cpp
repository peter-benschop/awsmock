//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/VersionIdsToStages.h>

namespace AwsMock::Dto::SecretsManager {

    view_or_value<view, value> VersionIdsToStages::ToDocument() const {

        /* Todo:
        try {

            Poco::JSON::Object rootJson;
            for (const auto &version: versions) {

                Poco::JSON::Object versionObject;
                Poco::JSON::Array stagesArray;
                for (const auto &stage: version.second) {
                    stagesArray.add(stage);
                }
                rootJson.set(version.first, stagesArray);
            }
            return rootJson;

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }*/
        return {};
    }

    void VersionIdsToStages::FromDocument(const view_or_value<view, value> &document) {

        /* Todo:
        try {

            //Core::JsonUtils::GetJsonValueString("Region", jsonObject, region);
            //Core::JsonUtils::GetJsonValueString("ARN", jsonObject, arn);

        } catch (Poco::Exception &exc) {
            std::cerr << exc.message() << std::endl;
            throw Core::ServiceException(exc.message());
        }*/
    }

    std::string VersionIdsToStages::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string VersionIdsToStages::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const VersionIdsToStages &r) {
        os << "VersionIdToStages=" + r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SecretsManager
