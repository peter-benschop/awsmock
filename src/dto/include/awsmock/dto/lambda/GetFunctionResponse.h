//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_GET_FUNCTION_REQUEST_H
#define AWSMOCK_DTO_LAMBDA_GET_FUNCTION_REQUEST_H

// C++ standard includes
#include <map>
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/lambda/Code.h>
#include <awsmock/dto/lambda/Environment.h>
#include <awsmock/dto/lambda/EphemeralStorage.h>

namespace AwsMock::Dto::Lambda {

    /**
   * Get function response
   *
   * Example:
   * <pre>
   * {
   *   "Code": {
   *      "ImageUri": "string",
   *      "Location": "string",
   *      "RepositoryType": "string",
   *      "ResolvedImageUri": "string"
   *   },
   *   "Concurrency": {
   *      "ReservedConcurrentExecutions": number
   *   },
   *   "Configuration": {
   *      "Architectures": [ "string" ],
   *      "CodeSha256": "string",
   *      "CodeSize": number,
   *      "DeadLetterConfig": {
   *         "TargetArn": "string"
   *      },
   *      "Description": "string",
   *      "Environment": {
   *         "Error": {
   *            "ErrorCode": "string",
   *            "Message": "string"
   *         },
   *         "Variables": {
   *            "string" : "string"
   *         }
   *      },
   *      "EphemeralStorage": {
   *         "Size": number
   *      },
   *      "FileSystemConfigs": [
   *         {
   *            "Arn": "string",
   *            "LocalMountPath": "string"
   *         }
   *      ],
   *      "FunctionArn": "string",
   *      "FunctionName": "string",
   *      "Handler": "string",
   *      "ImageConfigResponse": {
   *         "Error": {
   *            "ErrorCode": "string",
   *            "Message": "string"
   *         },
   *         "ImageConfig": {
   *            "Command": [ "string" ],
   *            "EntryPoint": [ "string" ],
   *            "WorkingDirectory": "string"
   *         }
   *      },
   *      "KMSKeyArn": "string",
   *      "LastModified": "string",
   *      "LastUpdateStatus": "string",
   *      "LastUpdateStatusReason": "string",
   *      "LastUpdateStatusReasonCode": "string",
   *      "Layers": [
   *         {
   *            "Arn": "string",
   *            "CodeSize": number,
   *            "SigningJobArn": "string",
   *            "SigningProfileVersionArn": "string"
   *         }
   *      ],
   *      "LoggingConfig": {
   *         "ApplicationLogLevel": "string",
   *         "LogFormat": "string",
   *         "LogGroup": "string",
   *         "SystemLogLevel": "string"
   *      },
   *      "MasterArn": "string",
   *      "MemorySize": number,
   *      "PackageType": "string",
   *      "RevisionId": "string",
   *      "Role": "string",
   *      "Runtime": "string",
   *      "RuntimeVersionConfig": {
   *         "Error": {
   *            "ErrorCode": "string",
   *            "Message": "string"
   *         },
   *         "RuntimeVersionArn": "string"
   *      },
   *      "SigningJobArn": "string",
   *      "SigningProfileVersionArn": "string",
   *      "SnapStart": {
   *         "ApplyOn": "string",
   *         "OptimizationStatus": "string"
   *      },
   *      "State": "string",
   *      "StateReason": "string",
   *      "StateReasonCode": "string",
   *      "Timeout": number,
   *      "TracingConfig": {
   *         "Mode": "string"
   *      },
   *      "Version": "string",
   *      "VpcConfig": {
   *         "Ipv6AllowedForDualStack": boolean,
   *         "SecurityGroupIds": [ "string" ],
   *         "SubnetIds": [ "string" ],
   *         "VpcId": "string"
   *      }
   *   },
   *   "Tags": {
   *      "string" : "string"
   *   }
   *}
   * </pre>
   */
    struct GetFunctionResponse {

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
     * @verbatim
     *"{\"JAVA_TOOL_OPTIONS\":\"-Duser.timezone=Europe/Berlin -Dspring.profiles.active=localhost\"}"
     * @endverbatim
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
        friend std::ostream &operator<<(std::ostream &os, const GetFunctionResponse &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_GET_FUNCTION_REQUEST_H
