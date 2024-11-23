//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/DescribeParametersRequest.h>

namespace AwsMock::Dto::SSM {

    std::string DescribeParametersRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("NextToken", nextToken);
            rootJson.set("MaxResults", maxResults);

            // Parameter filters
            Poco::JSON::Array jsonParameterFilterArray;
            for (const auto parameterFilter: parameterFilters) {
                jsonParameterFilterArray.add(parameterFilter.ToJsonObject());
            }
            rootJson.set("ParameterFilters", jsonParameterFilterArray);
            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    void DescribeParametersRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("NextToken", rootObject, nextToken);
            Core::JsonUtils::GetJsonValueInt("MaxResults", rootObject, maxResults);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string DescribeParametersRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeParametersRequest &r) {
        os << "DescribeParametersRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM
