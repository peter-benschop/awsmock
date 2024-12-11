//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/UserPool.h>

namespace AwsMock::Dto::Cognito {

    std::string UserPool::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> UserPool::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "UserPoolId", userPoolId);
            Core::Bson::BsonUtils::SetStringValue(document, "Arn", arn);
            Core::Bson::BsonUtils::SetDateValue(document, "CreationDate", created);
            Core::Bson::BsonUtils::SetDateValue(document, "LastModifiedDate", modified);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UserPool::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UserPool &o) {
        os << "UserPool=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
