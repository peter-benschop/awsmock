//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/TokenValidityUnits.h>

namespace AwsMock::Dto::Cognito {

    std::string TokenValidityUnits::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> TokenValidityUnits::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "AccessToken", ValidityUnitToString(accessToken));
            Core::Bson::BsonUtils::SetStringValue(document, "IdToken", ValidityUnitToString(idToken));
            Core::Bson::BsonUtils::SetStringValue(document, "RefreshToken", ValidityUnitToString(refreshToken));
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void TokenValidityUnits::FromDocument(const view_or_value<view, value> &document) {

        try {

            accessToken = ValidityUnitFromString(Core::Bson::BsonUtils::GetStringValue(document, "AccessToken"));
            idToken = ValidityUnitFromString(Core::Bson::BsonUtils::GetStringValue(document, "IdToken"));
            refreshToken = ValidityUnitFromString(Core::Bson::BsonUtils::GetStringValue(document, "RefreshToken"));

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string TokenValidityUnits::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TokenValidityUnits &o) {
        os << "TokenValidityUnits=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
