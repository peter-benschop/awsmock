//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_CONTAINER_H
#define AWSMOCK_DTO_DOCKER_CONTAINER_H

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
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/dto/docker/Port.h>

#define LAMBDA_INTERNAL_PORT 8080

namespace AwsMock::Dto::Docker {

    struct Container {

      /**
       * Image ID
       */
      std::string id;

      /**
       * Container names
       */
      std::vector<std::string> names;

      /**
       * Image
       */
      std::string image;

      /**
       * Image ID
       */
      std::string imageId;

      /**
       * Command
       */
      std::string command;

      /**
       * State
       */
      std::string state;

      /**
       * Status
       */
      std::string status;

      /**
       * Ports
       */
      std::vector<Port> ports;

      /**
       * Returns the lambda host port. The lambda host port is the public port for which the private port is 8080.
       *
       * @return lambda public port, or -1 if port does not exist.
       */
      int GetLambdaPort();

      /**
       * Convert to a JSON string
       *
       * @return JSON string
       */
      void FromJson(Poco::JSON::Object::Ptr object);

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
      friend std::ostream &operator<<(std::ostream &os, const Container &c);

    };

} // namespace AwsMock::Dto::Docker

#endif // AWSMOCK_DTO_DOCKER_CONTAINER_H
