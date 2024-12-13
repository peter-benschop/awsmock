//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/docker/CreateNetworkResponse.h>

namespace AwsMock::Dto::Docker {

    void CreateNetworkResponse::FromJson(const std::string &jsonString) {

        if (jsonString.empty()) {
            return;
        }

        try {

            const value document = bsoncxx::from_json(jsonString);
            id = Core::Bson::BsonUtils::GetStringValue(document, "Id");
            warning = Core::Bson::BsonUtils::GetStringValue(document, "Warning");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateNetworkResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "Warning", warning);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateNetworkResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateNetworkResponse &r) {
        os << "CreateNetworkResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
