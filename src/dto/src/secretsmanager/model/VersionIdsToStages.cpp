//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/model/VersionIdsToStages.h>

namespace AwsMock::Dto::SecretsManager {

    view_or_value<view, value> VersionIdsToStages::ToDocument() const {

        try {

            document rootDocument;
            if (!versions.empty()) {
                for (const auto &[fst, snd]: versions) {
                    array stagesArray;
                    document versionDocument;
                    for (const auto &stage: snd) {
                        stagesArray.append(stage);
                    }
                    versionDocument.append(kvp(fst, stagesArray));
                }
            }
            return rootDocument.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
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
