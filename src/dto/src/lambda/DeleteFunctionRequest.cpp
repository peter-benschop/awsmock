
#include <awsmock/dto/lambda/DeleteFunctionRequest.h>

namespace AwsMock::Dto::Lambda {

    std::string DeleteFunctionRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("FunctionName", functionName);
            rootJson.set("Qualifier", qualifier);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void DeleteFunctionRequest::FromJson(std::istream &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("FunctionName", rootObject, functionName);
            Core::JsonUtils::GetJsonValueString("Qualifier", rootObject, qualifier);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DeleteFunctionRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteFunctionRequest &r) {
        os << "DeleteFunctionRequest=" + r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
