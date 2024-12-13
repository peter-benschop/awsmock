//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/ValidationData.h>

namespace AwsMock::Dto::Cognito {

    std::string ValidationData::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void ValidationData::FromDocument(const view_or_value<view, value> &document) {

        try {

            name = Core::Bson::BsonUtils::GetStringValue(document, "Name");
            attributeValue = Core::Bson::BsonUtils::GetStringValue(document, "Value");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> ValidationData::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "Value", attributeValue);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ValidationData::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ValidationData &o) {
        os << "ValidationData=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
