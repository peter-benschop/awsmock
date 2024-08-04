//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateUserPoolClientResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string CreateUserPoolClientResponse::ToJson() const {

        try {

            Poco::JSON::Object rootObject;
            rootObject.set("Region", region);
            rootObject.set("UserGroupClient", userGroupClient.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateUserPoolClientResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateUserPoolClientResponse &r) {
        os << "CreateUserPoolClientResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito