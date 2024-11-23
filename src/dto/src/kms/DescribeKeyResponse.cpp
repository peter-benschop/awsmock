//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/DescribeKeyResponse.h>

namespace AwsMock::Dto::KMS {

    std::string DescribeKeyResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("KeyMetadata", key.ToJsonObject());
            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DescribeKeyResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeKeyResponse &r) {
        os << "DescribeKeyResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
