//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SSM_GET_PARAMETER_REQUEST_H
#define AWSMOCK_DTO_SSM_GET_PARAMETER_REQUEST_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::SSM {

    struct GetParameterRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Parameter name
         */
        std::string name;

        /**
         * WIth description
         */
        bool withDescription;

        /**
         * AWS request ID
         */
        std::string requestId;

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the JSON string to DTO.
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const GetParameterRequest &r);
    };

}// namespace AwsMock::Dto::SSM

#endif// AWSMOCK_DTO_SSM_GET_PARAMETER_REQUEST_H
