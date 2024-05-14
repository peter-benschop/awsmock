//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_DELETE_FUNCTION_REQUEST_H
#define AWSMOCK_DTO_LAMBDA_DELETE_FUNCTION_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

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
         * @param jsonString JSON string
         */
        void FromJson(std::istream &jsonString) {

            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);
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
            os << "DeleteFunctionRequest={functionName='" << r.functionName << "', qualifier: '" << r.qualifier << "'}";
            return os;
        }
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_DELETE_FUNCTION_REQUEST_H
