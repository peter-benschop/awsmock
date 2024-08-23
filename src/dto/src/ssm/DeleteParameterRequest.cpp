//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/DeleteParameterRequest.h>

namespace AwsMock::Dto::SSM {

    std::string DeleteParameterRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Name", name);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    void DeleteParameterRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Name", rootObject, name);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string DeleteParameterRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteParameterRequest &r) {
        os << "DeleteParameterRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM
