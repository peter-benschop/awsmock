//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_DELETEFUNCTIONREQUEST_H
#define AWSMOCK_DTO_LAMBDA_DELETEFUNCTIONREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::Lambda {

    struct DeleteFunctionRequest {

      /**
       * Name of the function
       */
      std::string functionName;

      /**
       * Qualifier
       */
      std::string qualifier;

      /**
       * Parse a JSON stream
       *
       * @param body jsoninput stream
       * @return
       */
      void FromJson(std::istream &body) {

          Poco::JSON::Parser parser;
          Poco::Dynamic::Var result = parser.parse(body);
          Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

          try {

              // Attributes
              Core::JsonUtils::GetJsonValueString("FunctionName", rootObject, functionName);
              Core::JsonUtils::GetJsonValueString("Qualifier", rootObject, qualifier);

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
      friend std::ostream &operator<<(std::ostream &os, const DeleteFunctionRequest &r) {
          os << "DeleteFunctionRequest={functionName='" + r.functionName + "' qualifier: '" + r.qualifier + "}";
          return os;
      }
      
    };

} // namespace AwsMock::Dto::Lambda

#endif // AWSMOCK_DTO_LAMBDA_DELETEFUNCTIONREQUEST_H
