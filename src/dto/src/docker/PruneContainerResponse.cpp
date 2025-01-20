//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/PruneContainerResponse.h>

namespace AwsMock::Dto::Docker {

    std::string PruneContainerResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetLongValue(document, "SpaceReclaimed", spaceReclaimed);

            if (!containersDeleted.empty()) {
                array jsonArray;
                for (const auto &container: containersDeleted) {
                    jsonArray.append(container);
                }
                document.append(kvp("deletedContainer", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &e) {
            log_error << e.what();
            throw Core::JsonException(e.what());
        }
    }

    void PruneContainerResponse::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);

            spaceReclaimed = Core::Bson::BsonUtils::GetLongValue(document, "SpaceReclaimed");

            if (spaceReclaimed > 0) {
                if (document.find("ContainersDeleted") != document.end()) {
                    for (const bsoncxx::array::view jsonArray = document.view()["ContainersDeleted"].get_array().value; const auto &container: jsonArray) {
                        containersDeleted.emplace_back(container.get_string().value);
                    }
                }
            }

        } catch (bsoncxx::exception &e) {
            log_error << e.what();
            throw Core::JsonException(e.what());
        }
    }

    std::string PruneContainerResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PruneContainerResponse &i) {
        os << "PruneContainerResponse=" << i.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
