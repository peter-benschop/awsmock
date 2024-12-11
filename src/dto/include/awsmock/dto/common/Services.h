//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_DTO_COMMON_SERVICES_H
#define AWSMOCK_DTO_COMMON_SERVICES_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/entity/cognito/UserPool.h>
#include <awsmock/entity/lambda/Lambda.h>

namespace AwsMock::Dto::Common {

    /**
     * @brief Services
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Services {

        /**
         * Service names
         */
        std::vector<std::string> serviceNames;

        /**
         * Check existence of given service name
         *
         * @param service name of the service
         * @return true in case the service exists
         */
        [[nodiscard]] bool HasService(const std::string &service) const;

        /**
         * Check existence of given service name
         *
         * @param service name of the service
         * @return true in case the service exists
         */
        [[nodiscard]] bool Contains(const std::string &service) const;

        /**
         * JSON representation
         *
         * @return Infrastructure as JSON string
         */
        std::string ToJson();

        /**
         * JSON representation
         *
         * @param payload HTTP request body
         */
        void FromJson(const std::string &payload);
    };

}// namespace AwsMock::Dto::Common

#endif// AWSMOCK_DTO_COMMON_SERVICES_H
