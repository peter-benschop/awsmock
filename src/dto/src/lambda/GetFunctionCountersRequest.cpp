//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/GetFunctionCountersRequest.h>

namespace AwsMock::Dto::Lambda {

    void GetFunctionCountersRequest::FromJson(const std::string &jsonString) {

        try {
            Poco::JSON::Parser parser;
            const Poco::Dynamic::Var result = parser.parse(jsonString);
            const Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

            Core::JsonUtils::GetJsonValueString("region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("functionName", rootObject, functionName);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string GetFunctionCountersRequest::ToJson() const {

        try {

            Poco::JSON::Object rootObject;

            rootObject.set("region", region);
            rootObject.set("functionName", functionName);

            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string GetFunctionCountersRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetFunctionCountersRequest &r) {
        os << "GetFunctionCountersRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
