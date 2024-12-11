//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/CreateContainerResponse.h>

namespace AwsMock::Dto::Docker {

    void CreateContainerResponse::FromJson(const std::string &jsonString) {

        if (jsonString.empty()) {
            return;
        }

        try {
            const value document = bsoncxx::from_json(jsonString);
            id = Core::Bson::BsonUtils::GetStringValue(document, "Id");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateContainerResponse::ToJson() const {
        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "id", id);
            Core::Bson::BsonUtils::SetIntValue(document, "hostPort", hostPort);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateContainerResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateContainerResponse &r) {
        os << "CreateContainerResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
