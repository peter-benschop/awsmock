//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/DescribeUserPoolClientResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string DescribeUserPoolClientResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("UserPoolClient", userPoolClient.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DescribeUserPoolClientResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeUserPoolClientResponse &r) {
        os << "DescribeUserPoolClientResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito