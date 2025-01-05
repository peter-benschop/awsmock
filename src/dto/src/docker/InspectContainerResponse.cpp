//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/InspectContainerResponse.h>

namespace AwsMock::Dto::Docker {

    void InspectContainerResponse::FromJson(const std::string &jsonString) {

        if (jsonString.empty()) {
            return;
        }

        try {
            const value document = bsoncxx::from_json(jsonString);
            id = Core::Bson::BsonUtils::GetStringValue(document, "Id");
            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");
            path = Core::Bson::BsonUtils::GetStringValue(document, "Path");
            image = Core::Bson::BsonUtils::GetStringValue(document, "Image");

            if (document.view().find("State") != document.view().end()) {
                state.FromDocument(document.view()["State"].get_document().value);
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string InspectContainerResponse::ToJson() const {
        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "Path", path);
            Core::Bson::BsonUtils::SetStringValue(document, "Image", image);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string InspectContainerResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const InspectContainerResponse &r) {
        os << "InspectContainerResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
