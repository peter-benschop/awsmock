//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/CreateUserResponse.h>

namespace AwsMock::Dto::Transfer {

    std::string CreateUserResponse::ToJson() const {

        // todo:
        /*
        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("ServerId", serverId);
            rootJson.set("UserName", userName);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/

        return {};
    }

    std::string CreateUserResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateUserResponse &r) {
        os << "CreateUserResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer
