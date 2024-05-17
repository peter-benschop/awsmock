//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateUserPoolResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string CreateUserPoolResponse::ToJson() const {

        try {

            Poco::JSON::Object rootObject;
            Poco::JSON::Object userPoolObject;
            userPoolObject.set("Region", region);
            userPoolObject.set("Name", name);
            rootObject.set("UserPool", userPoolObject);

            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateUserPoolResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateUserPoolResponse &r) {
        os << "CreateUserPoolResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito