//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/DescribeParametersResponse.h>

namespace AwsMock::Dto::SSM {

    std::string DescribeParametersResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("NextToken", nextToken);

            Poco::JSON::Array parameterArray;
            for (const auto &parameter: parameters) {
                parameterArray.add(parameter.ToJsonObject());
            }
            rootJson.set("Parameters", parameterArray);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string DescribeParametersResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeParametersResponse &r) {
        os << "DescribeParametersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM
