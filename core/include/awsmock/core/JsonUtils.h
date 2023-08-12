//
// Created by vogje01 on 22/08/2022.
//

#ifndef AWSMOCK_CORE_JSONUTILS_H
#define AWSMOCK_CORE_JSONUTILS_H

// Standard C++ includes
#include <string>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

namespace AwsMock::Core {

    /**
     * JSON utilities.
     *
     * @author jens.vogt@opitz-consulting.com
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

    public:
      /**
       * Extracts the supplied JSON value from the object.
       *
       * @param name name of the JSON attribute
       * @param jsonObject JSON parentObject
       * @param attribute JSON attribute
       */
      static void GetJsonValueLong(const std::string &name, Poco::JSON::Object::Ptr jsonObject, long &attribute);
    };

} // namespace AwsMock::Core
#endif // AWSMOCK_CORE_FILEUTILS_H
