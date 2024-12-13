//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/CreateKeyResponse.h>

namespace AwsMock::Dto::KMS {

    std::string CreateKeyResponse::ToJson() const {

        try {

            document document;
            document.append(kvp("KeyMetadata", key.ToDocument()));
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateKeyResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateKeyResponse &r) {
        os << "CreateKeyResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
