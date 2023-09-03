//
// Created by vogje01 on 21/06/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_ENVIRONMENT_H
#define AWSMOCK_DTO_LAMBDA_ENVIRONMENT_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::Lambda {

    struct Error {

      /**
       * Error code
       */
      std::string errorCode;

      /**
       * Error message
       */
      std::string message;

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const Error &r) {
          os << "Error={errorCode='" + r.errorCode + "' message='" + r.message + "'}";
          return os;
      }

    };

    struct EnvironmentVariables {

      /**
       * Environment variables
       */
      std::vector<std::pair<std::string, std::string>> variables;

      /**
       * Error
       */
      Error error;

      /**
       * Convert to a JSON string
       *
       * @return JSON string
       */
      [[nodiscard]] Poco::JSON::Object ToJson() const {

          Poco::JSON::Object environmentJson;
          try {

              Poco::JSON::Object errorJson;
              errorJson.set("ErrorCode", error.errorCode);
              errorJson.set("Message", error.message);

              Poco::JSON::Object variableJson;
              for(auto & variable : variables) {
                  variableJson.set(variable.first, variable.second);
              }

              environmentJson.set("Variables", variableJson);
              environmentJson.set("Error", errorJson);

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
          return environmentJson;
      }

      /**
       * Convert to a JSON string
       *
       * @return JSON string
       */
      void FromJson(Poco::JSON::Object::Ptr object) {

          try {

              Poco::JSON::Object::Ptr varObject = object->getObject("Variables");
              Poco::JSON::Object::NameList nameList = varObject->getNames();
              for (const auto &name : nameList) {
                  variables.emplace_back(name, varObject->get(name).convert<std::string>());
              }

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const EnvironmentVariables &r) {
          os << "EnvironmentVariables={variables=['";
          for (const auto &variable : r.variables) {
              os << variable.first << variable.second;
          }
          os << "] error:'" << r.error.ToString() << "'}";
          return os;
      }

    };

    struct Tags {

      /**
       * Tags
       */
      std::vector<std::pair<std::string, std::string>> tags;

      /**
       * Checks whether a tags with the given tags key exists.
       *
       * @param key key of the tags
       * @return true if tags with the given key exists.
       */
      bool HasTag(const std::string &key) {
          return find_if(tags.begin(), tags.end(), [key](const std::pair<std::string, std::string> &t) {
            return t.first == key;
          }) != tags.end();
      }

      /**
       * Returns a given tags value by key
       *
       * @param eventName name of the event
       * @return found notification or notifications.end().
       */
      std::string GetTagValue(const std::string &key) {
          auto it = find_if(tags.begin(), tags.end(), [key](const std::pair<std::string, std::string> &t) {
            return t.first == key;
          });
          return it->second;
      }

      /**
       * Convert to a JSON string
       *
       * @return JSON string
       */
      void FromJson(Poco::JSON::Object::Ptr object) {

          try {

              Poco::JSON::Object::NameList nameList = object->getNames();
              for (const auto &name : nameList) {
                  tags.emplace_back(name, object->get(name).convert<std::string>());
              }

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const Tags &r) {
          os << "Tags={tags=['";
          for (const auto &tag : r.tags) {
              os << tag.first << tag.second;
          }
          os << "]}";
          return os;
      }

    };
}
#endif //AWSMOCK_DTO_LAMBDA_ENVIRONMENT_H
