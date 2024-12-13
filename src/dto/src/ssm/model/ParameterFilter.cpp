//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/ssm/model/ParameterFilter.h>
#include <ranges>

namespace AwsMock::Dto::SSM {

    std::string ParameterFilter::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    view_or_value<view, value> ParameterFilter::ToDocument() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Key", key);
            Core::Bson::BsonUtils::SetStringValue(document, "Option", option);

            // Parameter filters
            if (!parameterFilters.empty()) {
                array jsonParameterFilterArray;
                for (const auto &element: parameterFilters) {
                    jsonParameterFilterArray.append(element.ToDocument());
                }
                document.append(kvp("ParameterFilters", jsonParameterFilterArray));
            }
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void ParameterFilter::FromDocument(const view_or_value<view, value> &document) {

        try {

            // Attributes
            key = Core::Bson::BsonUtils::GetStringValue(document, "Key");
            option = Core::Bson::BsonUtils::GetStringValue(document, "Option");

            // Parameter filters
            if (document.view().find("ParameterFilters") != document.view().end()) {
                for (const bsoncxx::array::view jsonParameterFilterArray = document.view()["ParameterFilters"].get_array().value; const auto &element: jsonParameterFilterArray) {
                    ParameterFilter parameterFilter;
                    parameterFilter.FromDocument(element.get_document().value);
                    parameterFilters.emplace_back(parameterFilter);
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ParameterFilter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ParameterFilter &r) {
        os << "ParameterFilter=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SSM
