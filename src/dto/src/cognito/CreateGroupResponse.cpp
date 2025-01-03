//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateGroupResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string CreateGroupResponse::ToJson() const {

        try {

            document document;
            document.append(kvp("Group", group.ToDocument()));
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateGroupResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateGroupResponse &r) {
        os << "CreateGroupResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito