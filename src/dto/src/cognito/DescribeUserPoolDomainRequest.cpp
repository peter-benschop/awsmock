//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/DescribeUserPoolDomainRequest.h>

namespace AwsMock::Dto::Cognito {

    void DescribeUserPoolDomainRequest::FromJson(const std::string &payload) {

        // TODO: Fix me
        /*Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("Domain", rootObject, domain);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
    }

    std::string DescribeUserPoolDomainRequest::ToJson() const {
        // TODO: Fix me
        /*
        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("Domain", domain);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    std::string DescribeUserPoolDomainRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeUserPoolDomainRequest &r) {
        os << "DescribeUserPoolDomainRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito