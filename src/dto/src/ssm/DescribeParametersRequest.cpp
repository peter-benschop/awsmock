//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/DescribeParametersRequest.h>

namespace AwsMock::Dto::SSM {

    std::string DescribeParametersRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "NextToken", nextToken);
            Core::Bson::BsonUtils::SetIntValue(document, "MaxResults", maxResults);

            if (!parameterFilters.empty()) {
                array jsonArray;
                for (const auto &filter: parameterFilters) {
                    jsonArray.append(filter.ToDocument());
                }
                document.append(kvp("ParameterFilters", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void DescribeParametersRequest::FromJson(const std::string &jsonString) {

        try {

            const value document = bsoncxx::from_json(jsonString);
            nextToken = Core::Bson::BsonUtils::GetStringValue(document, "NextToken");
            maxResults = Core::Bson::BsonUtils::GetIntValue(document, "MaxResults");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
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
