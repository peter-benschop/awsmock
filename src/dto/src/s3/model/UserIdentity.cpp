//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/model/UserIdentity.h>

namespace AwsMock::Dto::S3 {

    std::string UserIdentity::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "principalId", principalId);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> UserIdentity::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "principalId", principalId);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UserIdentity::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UserIdentity &r) {
        os << "UserIdentity=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::S3
