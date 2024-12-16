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
            Core::Bson::BsonUtils::SetStringValue(document, "id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "userPoolId", userPoolId);
            Core::Bson::BsonUtils::SetStringValue(document, "arn", arn);
            Core::Bson::BsonUtils::SetDateValue(document, "created", created);
            Core::Bson::BsonUtils::SetDateValue(document, "modified", modified);
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

    std::ostream &operator<<(std::ostream &os, const UserPool &r) {
        os << "UserPool=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
