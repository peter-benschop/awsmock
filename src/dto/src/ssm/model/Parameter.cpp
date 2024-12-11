//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/model/Parameter.h>

namespace AwsMock::Dto::SSM {

    view_or_value<view, value> Parameter::ToDocument() const {

        /* Todo
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Name", name);
            rootJson.set("Value", parameterValue);
            rootJson.set("Type", ParameterTypeToString(type));
            rootJson.set("Description", description);
            rootJson.set("KeyId", keyId);
            rootJson.set("ARN", arn);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    void Parameter::FromDocument(const view_or_value<view, value> &document) {

        /* Todo
        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Name", object, name);
            Core::JsonUtils::GetJsonValueString("Value", object, parameterValue);
            std::string typeStr;
            Core::JsonUtils::GetJsonValueString("Type", object, typeStr);
            type = ParameterTypeFromString(typeStr);
            Core::JsonUtils::GetJsonValueString("Description", object, description);
            Core::JsonUtils::GetJsonValueString("KeyId", object, keyId);
            Core::JsonUtils::GetJsonValueString("ARN", object, arn);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
    }

    std::string Parameter::ToJson() const {

        /* TOdo:
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Name", name);
            rootJson.set("Value", parameterValue);
            rootJson.set("Type", ParameterTypeToString(type));
            rootJson.set("Description", description);
            rootJson.set("KeyId", keyId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
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
