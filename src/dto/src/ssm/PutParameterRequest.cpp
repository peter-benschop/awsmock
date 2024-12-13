//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/PutParameterRequest.h>

namespace AwsMock::Dto::SSM {

    std::string PutParameterRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "Value", parameterValue);
            Core::Bson::BsonUtils::SetStringValue(document, "Type", ParameterTypeToString(type));
            Core::Bson::BsonUtils::SetStringValue(document, "Description", description);
            Core::Bson::BsonUtils::SetStringValue(document, "KeyId", keyId);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void PutParameterRequest::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");
            parameterValue = Core::Bson::BsonUtils::GetStringValue(document, "Value");
            type = ParameterTypeFromString(Core::Bson::BsonUtils::GetStringValue(document, "Type"));
            description = Core::Bson::BsonUtils::GetStringValue(document, "Description");
            keyId = Core::Bson::BsonUtils::GetStringValue(document, "KeyId");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string PutParameterRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutParameterRequest &r) {
        os << "PutParameterRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM
