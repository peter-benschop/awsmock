//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/UserIdentity.h>

namespace AwsMock::Dto::S3 {

    std::string UserIdentity::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("principalId", principalId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object UserIdentity::ToJsonObject() const {
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("principalId", principalId);
            return rootJson;
        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UserIdentity::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UserIdentity &r) {
        os << "UserIdentity=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::S3
