//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/docker/CreateContainerRequest.h>
#include <gtest/gtest.h>

namespace AwsMock::Dto::Docker {

    std::string CreateContainerRequest::ToJson() const {


        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Hostname", hostName);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Domainname", domainName);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "User", user);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Image", image);

            if (!environment.empty()) {
                array envArray;
                for (unsigned long i = 0; i < environment.size(); i++) {
                    envArray.append(environment[i]);
                }
                rootDocument.append(kvp("Env", envArray));
            }

            // Exposed ports
            document exposedPortsObject;
            exposedPortsObject.append(kvp(containerPort, make_document()));
            rootDocument.append(kvp("ExposedPorts", exposedPortsObject));

            // Host config
            document hostConfigObject;

            // Port array
            document hostPortObject;
            hostPortObject.append(kvp("HostPort", hostPort));

            // Host array
            array hostArray;
            hostArray.append(hostPortObject);

            // DNS array
            array dnsArray;
            dnsArray.append("8.8.8.8");
            hostConfigObject.append(kvp("Dns", dnsArray));

            // Port bindings
            document portBindingsObject;
            portBindingsObject.append(kvp(containerPort, hostArray));
            hostConfigObject.append(kvp("PortBindings", portBindingsObject));

            // Hosts docker internal, localstack (for localstack compatibility) and awsmock are routed to the docker host
            array extraHostsArray;
            extraHostsArray.append("host.docker.internal:host-gateway");
            extraHostsArray.append("awsmock:host-gateway");
            extraHostsArray.append("localstack:host-gateway");

            hostConfigObject.append(kvp("ExtraHosts", extraHostsArray));
            hostConfigObject.append(kvp("NetworkMode", networkMode));
            rootDocument.append(kvp("HostConfig", hostConfigObject));

            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }

        /*try {

            // Host config
            Poco::JSON::Object hostConfigObject;

            // Post array
            Poco::JSON::Object hostPortObject;
            hostPortObject.set("HostPort", hostPort);

            // Host array
            Poco::JSON::Array hostArray;
            hostArray.add(hostPortObject);

            // DNS array
            Poco::JSON::Array dnsArray;
            dnsArray.add("8.8.8.8");
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
        }*/
    }

    std::string CreateContainerRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateContainerRequest &r) {
        os << "CreateContainerRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
