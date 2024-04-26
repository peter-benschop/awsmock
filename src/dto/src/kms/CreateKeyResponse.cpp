//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/CreateKeyResponse.h>

namespace AwsMock::Dto::KMS {

    std::string CreateKeyResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("KeyMetadata", key.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateKeyResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateKeyResponse &r) {
        os << "CreateKeyResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
