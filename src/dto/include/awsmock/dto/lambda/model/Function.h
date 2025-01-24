//
// Created by vogje01 on 06/09/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_FUNCTION_H
#define AWSMOCK_DTO_LAMBDA_FUNCTION_H

// C++ standard includes
#include <chrono>
#include <map>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/dto/lambda/model/DeadLetterConfig.h>
#include <awsmock/dto/lambda/model/Environment.h>

namespace AwsMock::Dto::Lambda {

    struct Function {

        /**
         * AWS region
         */
        std::string region = {};

        /**
         * Architectures
         */
        std::vector<std::string> architectures = {};

        /**
         * SHA256 checksum
         */
        std::string codeSha256 = {};

        /**
         * Code size
         */
        long codeSize = 0;

        /**
         * Dead letter config
         */
        DeadLetterConfig deadLetterConfig = {};

        /**
         * Description
         */
        std::string description = {};
        // TODO: Environment, EpheremalStorage, FileSystemConfig

        /**
         * Function ARN
         */
        std::string functionArn = {};

        /**
         * Function name
         */
        std::string functionName = {};

        /**
         * Function handler
         */
        std::string handler = {};

        /**
         * Function runtime
         */
        std::string runtime = {};

        // TODO: ImageConfigResponse

        /**
         * Last modification datetime
         */
        system_clock::time_point lastModified = {};

        /**
         * Last update state
         */
        std::string lastUpdateStatus = {};

        /**
         * Last update state reason
         */
        std::string lastUpdateStatusReason = {};

        /**
         * Last update state reason
         */
        std::string lastUpdateStatusReasonCode = {};

        // TODO: Layers

        /**
         * State
         */
        std::string state = {};

        /**
         * State reason
         */
        std::string stateReason = {};

        /**
         * State reason code
         */
        std::string stateReasonCode = {};

        /**
         * Timeout
         */
        int timeout = 15 * 60;

        /**
         * Version
         */
        std::string version = "latest";

        /**
         * Environment
         */
        EnvironmentVariables environment = {};

        /**
         * Tags
         */
        std::map<std::string, std::string> tags = {};

        /**
         * Converts the DTO to a BSON document string.
         *
         * @return DTO as BSON document
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Function &f);
    };

    typedef std::vector<Function> FunctionList;

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_FUNCTION_H
