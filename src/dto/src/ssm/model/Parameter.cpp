//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/model/Parameter.h>

namespace AwsMock::Dto::SSM {

    view_or_value<view, value> Parameter::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "Value", parameterValue);
            Core::Bson::BsonUtils::SetStringValue(document, "Type", ParameterTypeToString(type));
            Core::Bson::BsonUtils::SetStringValue(document, "Description", description);
            Core::Bson::BsonUtils::SetStringValue(document, "KeyId", keyId);
            Core::Bson::BsonUtils::SetStringValue(document, "ARN", arn);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void Parameter::FromDocument(const view_or_value<view, value> &document) {

        try {

            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");
            parameterValue = Core::Bson::BsonUtils::GetStringValue(document, "Value");
            type = ParameterTypeFromString(Core::Bson::BsonUtils::GetStringValue(document, "Type"));
            description = Core::Bson::BsonUtils::GetStringValue(document, "Description");
            keyId = Core::Bson::BsonUtils::GetStringValue(document, "KeyId");
            arn = Core::Bson::BsonUtils::GetStringValue(document, "ARN");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Parameter::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Parameter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Parameter &r) {
        os << "Parameter=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM
