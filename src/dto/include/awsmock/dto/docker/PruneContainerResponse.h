//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_PRUNE_CONTAINER_RESPONSE_H
#define AWSMOCK_DTO_DOCKER_PRUNE_CONTAINER_RESPONSE_H

// C++ includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::Docker {

    /**
     * Prune docker response
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct PruneContainerResponse {

        /**
         * Image ID
         */
        std::vector<std::string> containersDeleted;

        /**
         * Space reclaimed
         */
        long spaceReclaimed;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Convert to a JSON string
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

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
        friend std::ostream &operator<<(std::ostream &os, const PruneContainerResponse &i);
    };

}// namespace AwsMock::Dto::Docker

#endif// AWSMOCK_DTO_DOCKER_PRUNE_CONTAINER_RESPONSE_H
