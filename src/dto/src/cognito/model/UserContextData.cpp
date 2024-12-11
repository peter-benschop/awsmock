//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/UserContextData.h>

namespace AwsMock::Dto::Cognito {

    std::string UserContextData::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> UserContextData::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "EncodedData", encodedData);
            Core::Bson::BsonUtils::SetStringValue(document, "IpAddress", ipAddress);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UserContextData::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UserContextData &o) {
        os << "UserContextData=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
