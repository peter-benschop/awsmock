//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_CREATE_FUNCTION_REQUEST_H
#define AWSMOCK_DTO_LAMBDA_CREATE_FUNCTION_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/lambda/Code.h>
#include <awsmock/dto/lambda/Environment.h>
#include <awsmock/dto/lambda/EphemeralStorage.h>

namespace AwsMock::Dto::Lambda {

    struct CreateFunctionRequest {

        /**
     * Region
     */
        std::string region;

        /**
     * User
     */
        std::string user;

        /**
     * Name of the function
     */
        std::string functionName;

        /**
     * Runtime environment
     */
        std::string runtime;

        /**
     * Role
     */
        std::string role;

        /**
     * Role
     */
        std::string handler;

        /**
     * Environment
     */
        EnvironmentVariables environmentVariables;

        /**
     * Memory size in MB. Default: 128, Range: 128 - 10240 MB
     */
        long memorySize = 128;

        /**
     * Temporary disk space in MB
     */
        EphemeralStorage ephemeralStorage;

        /**
     * Code
     */
        Code code;

        /**
     * Tags
     */
        std::map<std::string, std::string> tags;

        /**
     * Timeout
     */
        int timeout = 3;

        /**
     * Creates a JSON string from the object.
     *
     * @return JSON string
     */
        [[nodiscard]] std::string ToJson() const;

        /**
     * Parse a JSON stream.
     *
     * @code{.json}
     *"{\"JAVA_TOOL_OPTIONS\":\"-Duser.timezone=Europe/Berlin -Dspring.profiles.active=localhost\"}"
     * @endcode
     *
     * @param jsonString JSON string
     */
        void FromJson(const std::string &jsonString);

        /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
        [[nodiscard]] std::string ToString() const;

        /**
     * Stream provider.
     *
     * @return output stream
     */
        friend std::ostream &operator<<(std::ostream &os, const CreateFunctionRequest &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_CREATE_FUNCTION_REQUEST_H
