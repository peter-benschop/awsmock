//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/DescribeUserPoolResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string DescribeUserPoolResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("UserPool", userPool.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DescribeUserPoolResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeUserPoolResponse &r) {
        os << "DescribeUserPoolResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito