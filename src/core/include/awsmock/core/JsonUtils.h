//
// Created by vogje01 on 22/08/2022.
//

#ifndef AWS_MOCK_CORE_JSON_UTILS_H
#define AWS_MOCK_CORE_JSON_UTILS_H

// Standard C++ includes
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

#define JSON_DEFAULT_INDENT 4

namespace AwsMock::Core {

    /**
     * JSON utilities.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class JsonUtils {

      public:

        /**
         * Extracts the supplied JSON value from the object.
         *
         * @param name name of the JSON attribute
         * @param jsonObject JSON parentObject
         * @param attribute JSON attribute
         */
        static void GetJsonValueString(const std::string &name, Poco::JSON::Object::Ptr jsonObject, std::string &attribute);

        /**
         * Extracts the supplied JSON value from the object.
         *
         * @param name name of the JSON attribute
         * @param jsonObject JSON parentObject
         * @param attribute JSON attribute
         */
        static void GetJsonValueLong(const std::string &name, Poco::JSON::Object::Ptr jsonObject, long &attribute);

        /**
         * Extracts the supplied JSON value from the object.
         *
         * @param name name of the JSON attribute
         * @param jsonObject JSON parentObject
         * @param attribute JSON attribute
         */
        static void GetJsonValueDouble(const std::string &name, Poco::JSON::Object::Ptr jsonObject, double &attribute);

        /**
         * Extracts the supplied JSON value from the object.
         *
         * @param name name of the JSON attribute
         * @param jsonObject JSON parentObject
         * @param attribute JSON attribute
         */
        static void GetJsonValueFloat(const std::string &name, Poco::JSON::Object::Ptr jsonObject, float &attribute);

        /**
         * Extracts the supplied JSON value from the object.
         *
         * @param name name of the JSON attribute
         * @param jsonObject JSON parentObject
         * @param attribute JSON attribute
         */
        static void GetJsonValueInt(const std::string &name, Poco::JSON::Object::Ptr jsonObject, int &attribute);

        /**
         * Extracts the supplied JSON value from the object.
         *
         * @param name name of the JSON attribute
         * @param jsonObject JSON parentObject
         * @param attribute JSON attribute
         */
        static void GetJsonValueBool(const std::string &name, Poco::JSON::Object::Ptr jsonObject, bool &attribute);

        /**
         * Extracts the supplied JSON value from the object.
         *
         * @param name name of the JSON attribute
         * @param jsonObject JSON parentObject
         * @param attribute JSON attribute
         */
        static void GetJsonValueDate(const std::string &name, Poco::JSON::Object::Ptr jsonObject, Poco::DateTime &attribute);

        /**
         * Creates a JSON string array.
         *
         * @param values vector of string values
         * @return JSON string array
         */
        static Poco::JSON::Array GetJsonStringArray(const std::vector<std::string> &values);

        /**
         * Creates a JSON object from a string map.
         *
         * <p>
         * Each key, value pair will be converted to a attribute with name key and value=value.
         * </p>
         *
         * Example map<std::string, std::string>:
         * @code{.json}
         * {
         *  "map.first": "map.second"
         * }
         * </pre
         *
         * @param values vector of string values
         * @return JSON object
         */
        static Poco::JSON::Object GetJsonObject(const std::map<std::string, std::string> &values);

        /**
         * Returns the JSON string for the document.
         *
         * @param jsonObject JSON object
         * @param prettyPrint use indentation
         * @param indent indentation size
         * @return JSON string
         */
        static std::string ToJsonString(const Poco::JSON::Object &jsonObject, bool prettyPrint = false, int indent = JSON_DEFAULT_INDENT);

        /**
         * Returns the JSON string for the array.
         *
         * @param jsonArray JSON array
         * @param prettyPrint use indentation
         * @param indent indentation size
         * @return JSON string
         */
        static std::string ToJsonString(const Poco::JSON::Array &jsonArray, bool prettyPrint = false, int indent = JSON_DEFAULT_INDENT);
    };

}// namespace AwsMock::Core

#endif// AWS_MOCK_CORE_JSON_UTILS_H
