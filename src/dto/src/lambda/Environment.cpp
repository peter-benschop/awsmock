//
// Created by vogje01 on 21/06/2023.
//

#include <awsmock/dto/lambda/model/Environment.h>

namespace AwsMock::Dto::Lambda {

    Poco::JSON::Object EnvironmentVariables::ToJsonObject() const {

        Poco::JSON::Object environmentJson;
        try {

            Poco::JSON::Object variableJson;
            for (auto &variable: variables) {
                variableJson.set(variable.first, variable.second);
            }
            environmentJson.set("Variables", variableJson);

            Poco::JSON::Object errorJson;
            errorJson.set("ErrorCode", error.errorCode);
            errorJson.set("Message", error.message);
            environmentJson.set("Error", errorJson);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), 500);
        }
        return environmentJson;
    }

    void EnvironmentVariables::FromJson(Poco::JSON::Object::Ptr object) {

        try {

            Poco::JSON::Object::Ptr varObject = object->getObject("Variables");
            Poco::JSON::Object::NameList nameList = varObject->getNames();
            for (const auto &name: nameList) {
                variables[name] = varObject->get(name).convert<std::string>();
            }

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), 500);
        }
    }

    std::string EnvironmentVariables::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string EnvironmentVariables::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const EnvironmentVariables &r) {
        os << "EnvironmentVariables=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
