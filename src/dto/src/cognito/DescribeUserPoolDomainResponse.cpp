//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/DescribeUserPoolDomainResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string DescribeUserPoolDomainResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("UserPoolId", userPoolId);
            rootJson.set("Domain", domain);
            rootJson.set("Status", status);
            rootJson.set("S3Bucket", s3Bucket);
            rootJson.set("Version", version);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DescribeUserPoolDomainResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeUserPoolDomainResponse &r) {
        os << "DescribeUserPoolDomainResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito