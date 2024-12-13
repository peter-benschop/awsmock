//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/PutParameterResponse.h>

namespace AwsMock::Dto::SSM {

    std::string PutParameterResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Tier", tier);
            Core::Bson::BsonUtils::SetIntValue(document, "Version", version);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void PutParameterResponse::FromJson(const std::string &jsonString) {
        try {

            const value document = bsoncxx::from_json(jsonString);
            tier = Core::Bson::BsonUtils::GetStringValue(document, "Tier");
            version = Core::Bson::BsonUtils::GetIntValue(document, "Version");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string PutParameterResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutParameterResponse &r) {
        os << "PutParameterResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM
