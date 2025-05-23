//
// Created by vogje01 on 4/28/24.
//

#ifndef AWSMOCK_DTO_S3_FILTER_RULE_H
#define AWSMOCK_DTO_S3_FILTER_RULE_H

// C++ standard includes
#include <map>
#include <string>

// Boost includes
#include <boost/describe.hpp>
#include <boost/json.hpp>
#include <boost/mp11.hpp>
#include <boost/version.hpp>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/dto/common/BaseDto.h>

namespace AwsMock::Dto::S3 {

    /**
     * @brief S3 name type for the filter rules
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
     * @brief Filter rule for the S3 bucket notification to SQS queues
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct FilterRule final : Common::BaseDto<FilterRule> {

        /**
         * Name
         */
        NameType name;

        /**
         * Value
         */
        std::string filterValue;

        /**
         * @brief Converts the DTO to a JSON object.
         *
         * @return DTO as object.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts a JSON representation to s DTO.
         *
         * @param document JSON object.
         */
        void FromDocument(const view_or_value<view, value> &document);

        /**
         * @brief Convert from an XML string
         *
         * @param pt boost a property tree
         */
        void FromXml(const boost::property_tree::ptree &pt);

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        std::string ToJson() const override {
            return ToJson2();
        };

      private:

        friend void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, FilterRule const &obj) {
            jv = {
                    {"name", NameTypeToString(obj.name)},
                    {"filterValue", obj.filterValue},
            };
        }
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_FILTER_RULE_H
