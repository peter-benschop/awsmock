//
// Created by vogje01 on 8/23/24.
//

#ifndef AWSMOCK_DTO_SSM_MODEL_PARAMETER_H
#define AWSMOCK_DTO_SSM_MODEL_PARAMETER_H

// C++ standard includes
#include <map>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/ssm/model/ParameterType.h>

namespace AwsMock::Dto::SSM {

    /**
     * @brief SSM parameter
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Parameter {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Parameter name
         */
        std::string name;

        /**
         * Parameter value
         */
        std::string parameterValue;

        /**
         * Description
         */
        std::string description;

        /**
         * Parameter type
         */
        ParameterType type;

        /**
         * KMS key ID
         */
        std::string keyId;

        /**
         * Parameter tier
         */
        std::string tier;

        /**
         * AWS ARN
         */
        std::string arn;

        /**
         * Tags
         */
        std::map<std::string, std::string> tags;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts a JSON representation to s DTO.
         *
         * @param document JSON object.
         */
        void FromDocument(const view_or_value<view, value> &document);

        /**
         * @brief Converts the DTO to a JSON string.
         *
         * @return DTO as JSON string.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Parameter &r);
    };

}// namespace AwsMock::Dto::SSM

#endif// AWSMOCK_DTO_SSM_MODEL_PARAMETER_H
