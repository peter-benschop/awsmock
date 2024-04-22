//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_LIST_CONTAINER_RESPONSE_H
#define AWSMOCK_DTO_DOCKER_LIST_CONTAINER_RESPONSE_H

// C++ includes
#include <string>
#include <sstream>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/docker/Container.h>

namespace AwsMock::Dto::Docker {

  struct ListContainerResponse {

    /**
     * Container list
     */
    std::vector<Container> containerList;

    /**
     * Constructor
     */
    explicit ListContainerResponse(const std::string &body);

    /**
     * Convert to a JSON string
     *
     * @param jsonString JSON string
     */
    void FromJson(const std::string &jsonString);

    /**
     * Convert to a JSON string
     *
     * @param object JSON object
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
    friend std::ostream &operator<<(std::ostream &os, const ListContainerResponse &r);

  };

} // namespace AwsMock::Dto::Docker

#endif // AWSMOCK_DTO_DOCKER_LIST_CONTAINER_RESPONSE_H
