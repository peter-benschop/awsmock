//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/Group.h>

namespace AwsMock::Dto::Cognito {

    std::string Group::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> Group::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "GroupName", groupName);
            Core::Bson::BsonUtils::SetStringValue(document, "UserPoolId", userPoolId);
            Core::Bson::BsonUtils::SetStringValue(document, "Description", description);
            Core::Bson::BsonUtils::SetIntValue(document, "Precedence", precedence);
            Core::Bson::BsonUtils::SetLongValue(document, "CreationDate", Core::DateTimeUtils::UnixTimestamp(created));
            Core::Bson::BsonUtils::SetLongValue(document, "LastModifiedDate", Core::DateTimeUtils::UnixTimestamp(modified));
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Group::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Group &o) {
        os << "Group=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
