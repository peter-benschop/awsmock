//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_LISTCONTAINERRESPONSE_H
#define AWSMOCK_DTO_DOCKER_LISTCONTAINERRESPONSE_H

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
     * @return JSON string
     */
    void FromJson(const std::string &body);
  };

} // namespace AwsMock::Dto::Docker

#endif //AWSMOCK_DTO_DOCKER_LISTCONTAINERRESPONSE_H
