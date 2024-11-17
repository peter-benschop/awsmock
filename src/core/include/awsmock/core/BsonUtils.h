//
// Created by vogje01 on 11/17/24.
//

#ifndef AWS_MOCK_CORE_BSON_UTILS_H
#define AWS_MOCK_CORE_BSON_UTILS_H

// Boost includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>

namespace AwsMock::Core::Bson {

    using bsoncxx::builder::basic::array;
    using bsoncxx::builder::basic::document;
    using bsoncxx::document::value;

    template<class Element>
    void ToBsonArray(document &d, const std::string &name, std::vector<Element> a) {

        if (!a.empty()) {
            array jsonArray;
            for (const auto &e: a) {
                jsonArray.append(e.ToDocument());
            }
            d.append(kvp(name, jsonArray));
        }
    };

    template<class Element>
    void FromBsonArray(const bsoncxx::document::view &value, const std::string &name, std::vector<Element> *a) {

        if (value.find(name) != value.end()) {
            bsoncxx::array::view arrayView{value[name].get_array().value};
            for (const bsoncxx::array::element &arrayElement: arrayView) {
                Element element;
                element.FromDocument(arrayElement.get_document().view());
                a->emplace_back(element);
            }
        }
    };

    struct BsonUtils {

        static std::string GetOidValue(boost::optional<bsoncxx::document::view> &view, const std::string &name) {
            if (view.value().find(name) != view.value().end()) {
                return GetOidValue(view.value()[name]);
            }
            return {};
        }

        static std::string GetOidValue(const bsoncxx::document::element &element) {
            switch (element.type()) {
                case bsoncxx::type::k_null:
                    return {};
                case bsoncxx::type::k_oid:
                    return element.get_oid().value.to_string();
                case bsoncxx::type::k_double:
                case bsoncxx::type::k_string:
                case bsoncxx::type::k_document:
                case bsoncxx::type::k_array:
                case bsoncxx::type::k_binary:
                case bsoncxx::type::k_undefined:
                case bsoncxx::type::k_bool:
                case bsoncxx::type::k_date:
                case bsoncxx::type::k_regex:
                case bsoncxx::type::k_dbpointer:
                case bsoncxx::type::k_code:
                case bsoncxx::type::k_symbol:
                case bsoncxx::type::k_codewscope:
                case bsoncxx::type::k_int32:
                case bsoncxx::type::k_timestamp:
                case bsoncxx::type::k_int64:
                case bsoncxx::type::k_decimal128:
                case bsoncxx::type::k_maxkey:
                case bsoncxx::type::k_minkey:
                    break;
            }
            return {};
        }

        static long GetLongValue(boost::optional<bsoncxx::document::view> &view, const std::string &name) {
            if (view.value().find(name) != view.value().end()) {
                return GetLongValue(view.value()[name]);
            }
            return {};
        }

        static long GetLongValue(const bsoncxx::document::element &element) {

            switch (element.type()) {
                case bsoncxx::type::k_int32:
                    return static_cast<long>(element.get_int32().value);
                case bsoncxx::type::k_int64:
                    return static_cast<long>(element.get_int64().value);
                case bsoncxx::type::k_null:
                    return 0;
                case bsoncxx::type::k_double:
                case bsoncxx::type::k_string:
                case bsoncxx::type::k_document:
                case bsoncxx::type::k_array:
                case bsoncxx::type::k_binary:
                case bsoncxx::type::k_undefined:
                case bsoncxx::type::k_oid:
                case bsoncxx::type::k_bool:
                case bsoncxx::type::k_date:
                case bsoncxx::type::k_regex:
                case bsoncxx::type::k_dbpointer:
                case bsoncxx::type::k_code:
                case bsoncxx::type::k_symbol:
                case bsoncxx::type::k_codewscope:
                case bsoncxx::type::k_timestamp:
                case bsoncxx::type::k_decimal128:
                case bsoncxx::type::k_maxkey:
                case bsoncxx::type::k_minkey:
                    break;
            }
            return 0;
        }

        static int GetIntValue(boost::optional<bsoncxx::document::view> &view, const std::string &name) {
            if (view.value().find(name) != view.value().end()) {
                return GetIntValue(view.value()[name]);
            }
            return {};
        }

        static int GetIntValue(const bsoncxx::document::element &element) {

            switch (element.type()) {
                case bsoncxx::type::k_int32:
                    return static_cast<int>(element.get_int32().value);
                case bsoncxx::type::k_int64:
                    return static_cast<int>(element.get_int64().value);
                case bsoncxx::type::k_null:
                    return 0;
                case bsoncxx::type::k_double:
                case bsoncxx::type::k_string:
                case bsoncxx::type::k_document:
                case bsoncxx::type::k_array:
                case bsoncxx::type::k_binary:
                case bsoncxx::type::k_undefined:
                case bsoncxx::type::k_oid:
                case bsoncxx::type::k_bool:
                case bsoncxx::type::k_date:
                case bsoncxx::type::k_regex:
                case bsoncxx::type::k_dbpointer:
                case bsoncxx::type::k_code:
                case bsoncxx::type::k_symbol:
                case bsoncxx::type::k_codewscope:
                case bsoncxx::type::k_timestamp:
                case bsoncxx::type::k_decimal128:
                case bsoncxx::type::k_maxkey:
                case bsoncxx::type::k_minkey:
                    break;
            }
            return 0;
        }

        static double GetDoubleValue(boost::optional<bsoncxx::document::view> &view, const std::string &name) {
            if (view.value().find(name) != view.value().end()) {
                return GetDoubleValue(view.value()[name]);
            }
            return {};
        }

        static double GetDoubleValue(const bsoncxx::document::element &element) {

            switch (element.type()) {
                case bsoncxx::type::k_null:
                    return 0.0;
                case bsoncxx::type::k_double:
                    return static_cast<double>(element.get_double().value);
                case bsoncxx::type::k_int32:
                case bsoncxx::type::k_int64:
                case bsoncxx::type::k_string:
                case bsoncxx::type::k_document:
                case bsoncxx::type::k_array:
                case bsoncxx::type::k_binary:
                case bsoncxx::type::k_undefined:
                case bsoncxx::type::k_oid:
                case bsoncxx::type::k_bool:
                case bsoncxx::type::k_date:
                case bsoncxx::type::k_regex:
                case bsoncxx::type::k_dbpointer:
                case bsoncxx::type::k_code:
                case bsoncxx::type::k_symbol:
                case bsoncxx::type::k_codewscope:
                case bsoncxx::type::k_timestamp:
                case bsoncxx::type::k_decimal128:
                case bsoncxx::type::k_maxkey:
                case bsoncxx::type::k_minkey:
                    break;
            }
            return 0;
        }

        static std::string GetStringValue(boost::optional<bsoncxx::document::view> &view, const std::string &name) {
            if (view.value().find(name) != view.value().end()) {
                return GetStringValue(view.value()[name]);
            }
            return {};
        }

        static std::string GetStringValue(const bsoncxx::document::element &element) {
            switch (element.type()) {
                case bsoncxx::type::k_null:
                    return {};
                case bsoncxx::type::k_oid:
                    return element.get_oid().value.to_string();
                case bsoncxx::type::k_string:
                    return element.get_string().value.to_string();
                case bsoncxx::type::k_double:
                case bsoncxx::type::k_document:
                case bsoncxx::type::k_array:
                case bsoncxx::type::k_binary:
                case bsoncxx::type::k_undefined:
                case bsoncxx::type::k_bool:
                case bsoncxx::type::k_date:
                case bsoncxx::type::k_regex:
                case bsoncxx::type::k_dbpointer:
                case bsoncxx::type::k_code:
                case bsoncxx::type::k_symbol:
                case bsoncxx::type::k_codewscope:
                case bsoncxx::type::k_int32:
                case bsoncxx::type::k_timestamp:
                case bsoncxx::type::k_int64:
                case bsoncxx::type::k_decimal128:
                case bsoncxx::type::k_maxkey:
                case bsoncxx::type::k_minkey:
                    break;
            }
            return {};
        }

        static bool GetBoolValue(boost::optional<bsoncxx::document::view> &view, const std::string &name) {
            if (view.value().find(name) != view.value().end()) {
                return GetBoolValue(view.value()[name]);
            }
            return {};
        }

        static bool GetBoolValue(const bsoncxx::document::element &element) {
            switch (element.type()) {
                case bsoncxx::type::k_null:
                    return false;
                case bsoncxx::type::k_bool:
                    return element.get_bool().value;
                case bsoncxx::type::k_oid:
                case bsoncxx::type::k_string:
                case bsoncxx::type::k_double:
                case bsoncxx::type::k_document:
                case bsoncxx::type::k_array:
                case bsoncxx::type::k_binary:
                case bsoncxx::type::k_undefined:
                case bsoncxx::type::k_date:
                case bsoncxx::type::k_regex:
                case bsoncxx::type::k_dbpointer:
                case bsoncxx::type::k_code:
                case bsoncxx::type::k_symbol:
                case bsoncxx::type::k_codewscope:
                case bsoncxx::type::k_int32:
                case bsoncxx::type::k_timestamp:
                case bsoncxx::type::k_int64:
                case bsoncxx::type::k_decimal128:
                case bsoncxx::type::k_maxkey:
                case bsoncxx::type::k_minkey:
                    break;
            }
            return {};
        }
    };
}// namespace AwsMock::Core::Bson

#endif// AWS_MOCK_CORE_BSON_UTILS_H
