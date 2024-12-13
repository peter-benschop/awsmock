//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/DescribeKeyResponse.h>

namespace AwsMock::Dto::KMS {

    std::string DescribeKeyResponse::ToJson() const {

        try {

            document document;
            document.append(kvp("KeyMetadata", key.ToDocument()));
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
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
