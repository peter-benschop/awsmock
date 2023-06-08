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
       * Environment
       */
      std::vector<std::string> environment;

      /**
       * Exposed ports
       *
       * <p>Default is port 8080, which is the lambda internal port for invoking the lambda function. This will be mapped to the host network on port 9020 during the
       * start of the container.</p>
       */
      std::string exposedPorts;

      /**
       * Convert to a JSON string
       *
       * @return JSON string
       */
      std::string ToJson() {

          try {
              Poco::JSON::Object rootJson;
              rootJson.set("Hostname", hostName);
              rootJson.set("Domainname", domainName);
              rootJson.set("User", user);
              rootJson.set("Image", image);

              Poco::JSON::Array envArray;
              for(unsigned long i = 0; i < environment.size(); i++) {
                  envArray.set(i, environment[i]);
              }
              rootJson.set("Env", envArray);

              Poco::JSON::Object exposedPortsObject;
              exposedPortsObject.set(exposedPorts, Poco::JSON::Object());
              rootJson.set("ExposedPorts", exposedPortsObject);

              std::ostringstream os;
              rootJson.stringify(os);

              Poco::Logger::get("root").information("Container JSON: " + os.str());

              return os.str();

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const CreateContainerRequest &r) {
          os << "CreateContainerRequest={hostName='" + r.hostName + "' domainName='" + r.domainName + "' user='" + r.user + "' exposedPorts='" + r.exposedPorts + "' ";
          for(auto &it:r.environment) {
              os <<  it + ",";
          };
          os << "}";
          return os;
      }

    };

} // namespace AwsMock::Dto::Docker

#endif //AWSMOCK_DTO_DOCKER_CREATECONTAINERREQUEST_H
