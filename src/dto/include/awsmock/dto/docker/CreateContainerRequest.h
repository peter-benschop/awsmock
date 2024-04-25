//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_CREATECONTAINERREQUEST_H
#define AWSMOCK_DTO_DOCKER_CREATECONTAINERREQUEST_H

// C++ includes
#include <sstream>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::Docker {

    /**
     * Exposed port
     *
     * @author jens.vogt@opitz-consulting.com
     */
    struct ExposedPort {

        /**
         * Internal port
         */
        std::string internalPort;

        /**
         * Internal protocol
         */
        std::string protocol;
    };

    /**
     * Create container request
     *
     * @author jens.vogt@opitz-consulting.com
     */
    struct CreateContainerRequest {

        /**
         * Hostname
         */
        std::string hostName;

        /**
         * Domain name
         */
        std::string domainName;

        /**
         * User
         */
        std::string user;

        /**
         * Image
         */
        std::string image;

        /**
         * Network mode
         */
        std::string networkMode = "bridge";

        /**
         * Environment
         */
        std::vector<std::string> environment;

        /**
         * Container ports
         */
        std::string containerPort;

        /**
         * Host ports
         */
        std::string hostPort;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const CreateContainerRequest &r);
    };

}// namespace AwsMock::Dto::Docker

#endif//AWSMOCK_DTO_DOCKER_CREATECONTAINERREQUEST_H
