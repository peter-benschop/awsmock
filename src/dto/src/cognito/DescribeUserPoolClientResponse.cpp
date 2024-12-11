//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/DescribeUserPoolClientResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string DescribeUserPoolClientResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            document.append(kvp("UserPoolClient", userPoolClient.ToDocument()));
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DescribeUserPoolClientResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeUserPoolClientResponse &r) {
        os << "DescribeUserPoolClientResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito