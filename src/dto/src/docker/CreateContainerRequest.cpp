//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/docker/CreateContainerRequest.h>

namespace AwsMock::Dto::Docker {

    std::string CreateContainerRequest::ToJson() const {

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

            // Post array
            Poco::JSON::Object hostPortObject;
            hostPortObject.set("HostPort", hostPort);

            // Host array
            Poco::JSON::Array hostArray;
            hostArray.add(hostPortObject);

            // Host array
            Poco::JSON::Array dnsArray;
            //dnsArray.add("172.17.0.1");
            dnsArray.add("8.8.8.8");
            //            dnsArray.add("8.8.4.4");
            //            dnsArray.add("1.1.1.1");
            hostConfigObject.set("Dns", dnsArray);

            Poco::JSON::Object portBindingsObject;
            portBindingsObject.set(containerPort, hostArray);
            hostConfigObject.set("PortBindings", portBindingsObject);

            // Hosts docker internal, localstack (for localstack compatibility) and awsmock are routed to the docker host
            Poco::JSON::Array extraHostsArray;
            extraHostsArray.add("host.docker.internal:host-gateway");
            extraHostsArray.add("awsmock:host-gateway");
            extraHostsArray.add("localstack:host-gateway");

            hostConfigObject.set("ExtraHosts", extraHostsArray);
            hostConfigObject.set("NetworkMode", networkMode);
            rootJson.set("HostConfig", hostConfigObject);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateContainerRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateContainerRequest &r) {
        os << "CreateContainerRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
