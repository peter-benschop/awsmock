//
// Created by vogje01 on 8/23/24.
//

#ifndef AWSMOCK_DTO_SSM_MODEL_PARAMETER_FILTERS_H
#define AWSMOCK_DTO_SSM_MODEL_PARAMETER_FILTERS_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/ssm/model/ParameterFilter.h>

namespace AwsMock::Dto::SSM {

    /**
     * @brief SSM parameter filter
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ParameterFilter {

        /**
         * The name of the filter.
         */
        std::string key;

        /**
         * For all filters used with DescribeParameters, valid options include Equals and BeginsWith. The Name filter additionally supports
         * the Contains option. (Exception: For filters using the key Path, valid options include Recursive and OneLevel.)
         */
        std::string option;

        /**
         * Filters to limit the request results.
         */
        std::vector<ParameterFilter> parameterFilters;

        /**
         * @brief Converts the DTO to a JSON string.
         *
         * @return DTO as JSON string.
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const ParameterFilter &r);
    };

}// namespace AwsMock::Dto::SSM

#endif// AWSMOCK_DTO_SSM_MODEL_PARAMETER_FILTERS_H
