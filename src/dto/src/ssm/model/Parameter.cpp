//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/model/Parameter.h>

namespace AwsMock::Dto::SSM {

    std::string Parameter::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Name", name);
            rootJson.set("Value", value);
            rootJson.set("Type", ParameterTypeToString(type));
            rootJson.set("Description", description);
            rootJson.set("KeyId", keyId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object Parameter::ToJsonObject() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Name", name);
            rootJson.set("Value", value);
            rootJson.set("Type", ParameterTypeToString(type));
            rootJson.set("Description", description);
            rootJson.set("KeyId", keyId);
            rootJson.set("ARN", arn);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void Parameter::FromJsonObject(const Poco::JSON::Object::Ptr &object) {

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Name", object, name);
            Core::JsonUtils::GetJsonValueString("Value", object, value);
            std::string typeStr;
            Core::JsonUtils::GetJsonValueString("Type", object, typeStr);
            type = ParameterTypeFromString(typeStr);
            Core::JsonUtils::GetJsonValueString("Description", object, description);
            Core::JsonUtils::GetJsonValueString("KeyId", object, keyId);
            Core::JsonUtils::GetJsonValueString("ARN", object, arn);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Parameter::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Parameter &r) {
        os << "Parameter=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM
