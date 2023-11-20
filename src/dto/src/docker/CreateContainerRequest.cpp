//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/docker/CreateContainerRequest.h>

namespace AwsMock::Dto::Docker {

  std::string CreateContainerRequest::ToJson() {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Hostname", hostName);
      rootJson.set("Domainname", domainName);
      rootJson.set("User", user);
      rootJson.set("Image", image);

      Poco::JSON::Array envArray;
      for (unsigned long i = 0; i < environment.size(); i++) {
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

      // Hosts docker internal and awsmock are routed to the docker host
      Poco::JSON::Array extraHostsArray;
      extraHostsArray.add("host.docker.internal:host-gateway");
      extraHostsArray.add("awsmock:host-gateway");
      extraHostsArray.add("localstack:host-gateway");

      hostConfigObject.set("ExtraHosts", extraHostsArray);
      hostConfigObject.set("NetworkMode", networkMode);
      rootJson.set("HostConfig", hostConfigObject);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string CreateContainerRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateContainerRequest &r) {
    os << "CreateContainerRequest={hostName='" << r.hostName << "' domainName='" << r.domainName << "' user='" << r.user << "' containerPort='"
       << r.containerPort + "' ";
    for (auto &it : r.environment) {
      os << it << ",";
    };
    os << "}";
    return os;
  }

} // namespace AwsMock::Dto::Docker
