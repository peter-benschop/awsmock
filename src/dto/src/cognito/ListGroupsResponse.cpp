//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListGroupsResponse.h>

namespace AwsMock::Dto::Cognito {

    std::string ListGroupsResponse::ToJson() const {

        try {

            Poco::JSON::Object rootObject;
            Poco::JSON::Array groupsArray;
            for (const auto &group: groups) {
                groupsArray.add(group.ToJsonObject());
            }
            rootObject.set("Groups", groupsArray);

            return Core::JsonUtils::ToJsonString(rootObject);

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListGroupsResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListGroupsResponse &r) {
        os << "ListGroupsResponse=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito