//
// Created by vogje01 on 4/28/24.
//

#ifndef AWSMOCK_DTO_S3_FILTER_RULE_H
#define AWSMOCK_DTO_S3_FILTER_RULE_H

// C++ standard includes
#include <string>
#include <map>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::S3 {

    /**
     * S3 name type for the filter rules
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    enum class NameType {
        prefix,
        suffix
    };

    static std::map<NameType, std::string> NameTypeNames{
            {NameType::prefix, "prefix"},
            {NameType::suffix, "suffix"}};

    [[maybe_unused]] static std::string NameTypeToString(NameType nameType) {
        return NameTypeNames[nameType];
    }

    [[maybe_unused]] static NameType NameTypeFromString(const std::string &nameType) {
        for (auto &[fst, snd]: NameTypeNames) {
            if (snd == nameType) {
                return fst;
            }
        }
        return NameType::prefix;
    }

    /**
     * Filter rule for the S3 bucket notification to SQS queues
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct FilterRule {

        /**
         * Name
         */
        NameType name;

        /**
         * Value
         */
        std::string filterValue;

        /**
         * Converts the DTO to a JSON object.
         *
         * @return DTO as object.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * Converts the DTO to a JSON string.
         *
         * @return DTO as string.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Converts a JSON representation to s DTO.
         *
         * @param document JSON object.
         */
        void FromDocument(const view_or_value<view, value> &document);

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
        friend std::ostream &operator<<(std::ostream &os, const FilterRule &s);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_FILTER_RULE_H
