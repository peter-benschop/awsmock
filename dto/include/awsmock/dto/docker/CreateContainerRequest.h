//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_CREATECONTAINERREQUEST_H
#define AWSMOCK_DTO_DOCKER_CREATECONTAINERREQUEST_H

// C++ includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::Docker {

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
    std::string networkMode;

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
    std::string ToJson();

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

} // namespace AwsMock::Dto::Docker

#endif //AWSMOCK_DTO_DOCKER_CREATECONTAINERREQUEST_H
