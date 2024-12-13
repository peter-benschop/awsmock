//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/DescribeParametersResponse.h>

namespace AwsMock::Dto::SSM {

    std::string DescribeParametersResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "NextToken", nextToken);

            if (!parameters.empty()) {
                array jsonArray;
                for (const auto &parameter: parameters) {
                    jsonArray.append(parameter.ToDocument());
                }
                document.append(kvp("Parameters", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DescribeParametersResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeParametersResponse &r) {
        os << "DescribeParametersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM
