//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/Filter.h>

namespace AwsMock::Dto::SecretsManager {

    view_or_value<view, value> Filter::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Key", key);

            // Values
            if (!values.empty()) {
                array valuesArray;
                for (const auto &e: values) {
                    valuesArray.append(e);
                }
                document.append(kvp("Values", valuesArray));
            }
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void Filter::FromDocument(const view_or_value<view, value> &document) {

        try {

            key = Core::Bson::BsonUtils::GetStringValue(document, "Key");

            // Values
            if (document.view().find("Values") != document.view().end()) {
                for (const bsoncxx::array::view arrayView{document.view()["Values"].get_array().value}; const bsoncxx::array::element &element: arrayView) {
                    values.emplace_back(element.get_string().value);
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Filter::ToJson() const {

        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Filter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Filter &tags) {
        os << "Filter=" << tags.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SecretsManager