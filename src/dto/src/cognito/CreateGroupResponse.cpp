//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateGroupResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string CreateGroupResponse::ToJson() const {

        try {

            Poco::JSON::Object rootObject;
            rootObject.set("Group", group.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateGroupResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateGroupResponse &r) {
        os << "CreateUserPoolResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito