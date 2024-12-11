//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/DescribeUserPoolResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string DescribeUserPoolResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            document.append(kvp("UserPool", userPool.ToDocument()));
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DescribeUserPoolResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeUserPoolResponse &r) {
        os << "DescribeUserPoolResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito