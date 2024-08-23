//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/GetParameterRequest.h>

namespace AwsMock::Dto::SSM {

    std::string GetParameterRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Name", name);
            rootJson.set("WithDescription", withDescription);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    void GetParameterRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Name", rootObject, name);
            Core::JsonUtils::GetJsonValueBool("WithDescription", rootObject, withDescription);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string GetParameterRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetParameterRequest &r) {
        os << "GetParameterRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM
