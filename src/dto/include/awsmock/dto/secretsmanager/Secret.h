//
// Created by vogje01 on 4/11/24.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_SECRET_H
#define AWSMOCK_DTO_SECRETSMANAGER_SECRET_H


// C++ standard includes
#include <string>

// Boost includes
#include <boost/algorithm/string/find.hpp>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/dto/secretsmanager/RotationRules.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Secrets list filter
     *
     * Example:
     * @code{.json}
     *  {
     *     "Name": "string",
     *     "OwningService": "string",
     *     "ARN": "string",
     *     "Description": "string",
     *     "KmsKeyId": "string",
     *     "PrimaryRegion": "string",
     *     "CreatedDate": number,
     *     "DeletedDate": number,
     *     "LastAccessedDate": number,
     *     "LastChangedDate": number,
     *     "LastRotatedDate": number,
     *     "NextRotationDate": number,
     *     "RotationEnabled": boolean,
     *     "RotationLambdaARN": "string",
     *     "RotationRules": {
     *        "AutomaticallyAfterDays": number,
     *        "Duration": "string",
     *        "ScheduleExpression": "string"
     *     },
     *     "SecretVersionsToStages": {
     *        "string" : [ "string" ]
     *     },
     *     "Tags": [
     *       {
     *          "Key": "string",
     *          "Value": "string"
     *       }
     *    ]
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Secret {

        /**
         * AWS ARN
         */
        std::string arn;

        /**
         * Name
         */
        std::string name;

        /**
         * Description
         */
        std::string description;

        /**
         * KMS key ID
         */
        std::string kmsKeyId;

        /**
         * Secret owner
         */
        std::string owningService;

        /**
         * Primary region
         */
        std::string primaryRegion;

        /**
         * Creation date
         */
        long createdDate = 0;

        /**
         * Deleted date
         */
        long deletedDate = 0;

        /**
         * Last access date
         */
        long lastAccessedDate = 0;

        /**
         * Last changed date
         */
        long lastChangedDate = 0;

        /**
         * Last rotation date
         */
        long lastRotatedDate = 0;

        /**
         * Next rotation date
         */
        long nextRotatedDate = 0;

        /**
         * Next rotation date
         */
        bool rotationEnabled = false;

        /**
         * Rotation lambda ARN
         */
        std::string rotationLambdaARN;

        /**
         * Rotation rules
         */
        RotationRules rotationRules;

        /**
         * @brief Converts the DTO to a JSON object.
         *
         * @return DTO as JSON object.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the JSON object to DTO.
         *
         * @param document JSON object
         */
        void FromDocument(const view_or_value<view, value> &document);

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const Secret &f);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif//AWSMOCK_DTO_SECRETSMANAGER_SECRET_H
