//
// Created by vogje01 on 11/17/24.
//

#ifndef AWS_MOCK_CORE_BSON_UTILS_H
#define AWS_MOCK_CORE_BSON_UTILS_H

// C++ includes
#include <chrono>

// Bson includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/stdx.hpp>

namespace AwsMock::Core::Bson {

    using bsoncxx::builder::basic::array;
    using bsoncxx::builder::basic::document;
    using bsoncxx::document::value;
    using std::chrono::system_clock;

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

        static std::string GetOidValue(mongocxx::stdx::optional<bsoncxx::document::view> &view, const std::string &name) {
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
                default:
                    break;
            }
            return {};
        }

        static long GetLongValue(mongocxx::stdx::optional<bsoncxx::document::view> &view, const std::string &name) {
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
                default:
                    break;
            }
            return 0;
        }

        static int GetIntValue(mongocxx::stdx::optional<bsoncxx::document::view> &view, const std::string &name) {
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
                default:
                    break;
            }
            return 0;
        }

        static double GetDoubleValue(mongocxx::stdx::optional<bsoncxx::document::view> &view, const std::string &name) {
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
                default:
                    break;
            }
            return 0;
        }

        static std::string GetStringValue(mongocxx::stdx::optional<bsoncxx::document::view> &view, const std::string &name) {
            if (view.value().find(name) != view.value().end()) {
                return GetStringValue(view.value()[name]);
            }
            return {};
        }

        static std::string GetStringValue(const bsoncxx::document::element &element) {
            switch (element.type()) {
                case bsoncxx::type::k_null:
                    return {};
                case bsoncxx::type::k_string:
                    return bsoncxx::string::to_string(element.get_string().value);
                default:
                    break;
            }
            return {};
        }

        static bool GetBoolValue(mongocxx::stdx::optional<bsoncxx::document::view> &view, const std::string &name) {
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
                default:
                    break;
            }
            return {};
        }

        static system_clock::time_point GetDateValue(mongocxx::stdx::optional<bsoncxx::document::view> &view, const std::string &name) {
            if (view.value().find(name) != view.value().end()) {
                return GetDateValue(view.value()[name]);
            }
            return {};
        }

        static system_clock::time_point GetDateValue(const bsoncxx::document::element &element) {
            switch (element.type()) {
                case bsoncxx::type::k_null:
                    return system_clock::now();
                case bsoncxx::type::k_date:
                    return bsoncxx::types::b_date(element.get_date());
                default:
                    break;
            }
            return {};
        }
    };
}// namespace AwsMock::Core::Bson

#endif// AWS_MOCK_CORE_BSON_UTILS_H
