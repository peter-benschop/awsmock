//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/GetParameterResponse.h>

namespace AwsMock::Dto::SSM {

    std::string GetParameterResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Parameter", parameter.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string GetParameterResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetParameterResponse &r) {
        os << "GetParameterResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM
