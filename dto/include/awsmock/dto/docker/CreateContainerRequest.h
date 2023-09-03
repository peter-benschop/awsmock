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
      std::string ToJson() {

          try {
              Poco::JSON::Object rootJson;
              rootJson.set("Hostname", hostName);
              rootJson.set("Domainname", domainName);
              rootJson.set("User", user);
              rootJson.set("Image", image);
              rootJson.set("NetworkMode", networkMode);

              Poco::JSON::Array envArray;
              for(unsigned long i = 0; i < environment.size(); i++) {
                  envArray.set(i, environment[i]);
              }
              rootJson.set("Env", envArray);

              // Exposed ports
              Poco::JSON::Object exposedPortsObject;
              exposedPortsObject.set(containerPort, Poco::JSON::Object());
              rootJson.set("ExposedPorts", exposedPortsObject);

              // Host config
              Poco::JSON::Object hostConfigObject;

              Poco::JSON::Object hostPortObject;
              hostPortObject.set("HostPort", hostPort);

              Poco::JSON::Array hostArray;
              hostArray.add(hostPortObject);

              Poco::JSON::Object portBindingsObject;
              portBindingsObject.set(containerPort, hostArray);

              hostConfigObject.set("PortBindings", portBindingsObject);

              Poco::JSON::Array extraHostsArray;
              extraHostsArray.add("host.docker.internal:172.17.0.1");

              hostConfigObject.set("ExtraHosts", extraHostsArray);
              rootJson.set("HostConfig", hostConfigObject);

              std::ostringstream os;
              rootJson.stringify(os);
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
          os << "CreateContainerRequest={hostName='" << r.hostName << "' domainName='" << r.domainName << "' user='" << r.user << "' containerPort='" << r.containerPort + "' ";
          for(auto &it:r.environment) {
              os <<  it << ",";
          };
          os << "}";
          return os;
      }

    };

} // namespace AwsMock::Dto::Docker

#endif //AWSMOCK_DTO_DOCKER_CREATECONTAINERREQUEST_H
