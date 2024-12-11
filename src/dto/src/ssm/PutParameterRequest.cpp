//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/PutParameterRequest.h>

namespace AwsMock::Dto::SSM {

    std::string PutParameterRequest::ToJson() const {

        /* Todo:
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
            throw Core::ServiceException(exc.message());
        }*/
        return {};
    }

    void PutParameterRequest::FromJson(const std::string &jsonString) {

        /* Todo:
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Name", rootObject, name);
            Core::JsonUtils::GetJsonValueString("Value", rootObject, value);
            std::string typeStr;
            Core::JsonUtils::GetJsonValueString("Type", rootObject, typeStr);
            type = ParameterTypeFromString(typeStr);
            Core::JsonUtils::GetJsonValueString("Description", rootObject, description);
            Core::JsonUtils::GetJsonValueString("KeyId", rootObject, keyId);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }*/
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
