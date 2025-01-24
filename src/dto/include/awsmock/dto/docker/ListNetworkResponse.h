//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_LIST_NETWORK_RESPONSE_H
#define AWSMOCK_DTO_DOCKER_LIST_NETWORK_RESPONSE_H

// C++ includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/dto/docker/model/Network.h>

namespace AwsMock::Dto::Docker {

    /**
     * @brief List networks response
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListNetworkResponse {

        /**
         * Network list
         */
        std::vector<Network> networkList;

        /**
         * @brief Convert to a JSON string
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * @brief Convert to a JSON string
         *
         * @return object JSON string
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
        friend std::ostream &operator<<(std::ostream &os, const ListNetworkResponse &r);
    };

}// namespace AwsMock::Dto::Docker

#endif// AWSMOCK_DTO_DOCKER_LIST_NETWORK_RESPONSE_H
