//
// Created by vogje01 on 4/28/24.
//

#include <awsmock/dto/s3/model/FilterRule.h>

namespace AwsMock::Dto::S3 {

    view_or_value<view, value> FilterRule::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "name", NameTypeToString(name));
            Core::Bson::BsonUtils::SetStringValue(document, "value", filterValue);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string FilterRule::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    void FilterRule::FromDocument(const view_or_value<view, value> &document) {

        try {

            name = NameTypeFromString(Core::Bson::BsonUtils::GetStringValue(document, "name"));
            filterValue = Core::Bson::BsonUtils::GetStringValue(document, "value");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string FilterRule::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const FilterRule &s) {
        os << "FilterRule=" << s.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
