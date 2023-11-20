//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_TRANSFER_LISTSERVERRESPONSE_H
#define AWSMOCK_DTO_TRANSFER_LISTSERVERRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/dto/lambda/CreateFunctionResponse.h>

namespace AwsMock::Dto::Transfer {

  struct Server {

    /**
     * ARN
     */
    std::string arn;

    /**
     * Domain
     */
    std::string domain;

    /**
     * Identity provider type
     */
    std::string identityProviderType;

    /**
     * Endpoint type
     */
    std::string endpointType;

    /**
     * Logging role
     */
    std::string loggingRole;

    /**
     * Server ID
     */
    std::string serverId;

    /**
     * State
     */
    std::string state;

    /**
     * User count
     */
    int userCount;

    /**
     * Converts the DTO to a JSON representation.
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] Poco::JSON::Object ToJsonObject() const {

      try {
        Poco::JSON::Object rootJson;
        rootJson.set("Arn", arn);
        rootJson.set("Domain", domain);
        rootJson.set("IdentityProviderType", identityProviderType);
        rootJson.set("EndpointType", endpointType);
        rootJson.set("LoggingRole", loggingRole);
        rootJson.set("ServerId", serverId);
        rootJson.set("State", state);
        rootJson.set("UserCount", userCount);

        return rootJson;

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
    friend std::ostream &operator<<(std::ostream &os, const Server &r) {
      os << "Server={arn='" << r.arn << "' domain='" << r.domain << "' identityProviderType='" << r.identityProviderType << "' endpointType='" << r.endpointType
         << "' loggingRole='" << r.loggingRole << "' serverId='" << r.serverId << "' state='" << r.state << "' userCount='" << r.userCount << "'}";
      return os;
    }
  };

  struct ListServerResponse {

    /**
     * Region
     */
    std::string region;

    /**
     * Next token ID
     */
    std::string nextToken;

    /**
     * Server list
     */
    std::vector<Server> servers;

    /**
     * Creates a JSON string from the object.
     *
     * @return JSON string
     */
    std::string ToJson() {

      try {
        Poco::JSON::Object rootJson;
        //rootJson.set("Region", region);
        //rootJson.set("NextToken", null);

        Poco::JSON::Array serversJsonArray;
        for (const auto &server : servers) {
          serversJsonArray.add(server.ToJsonObject());
        }
        rootJson.set("Servers", serversJsonArray);

        std::ostringstream os;
        rootJson.stringify(os);
        return os.str();

      } catch (Poco::Exception &exc) {
        throw Core::ServiceException(exc.message(), 500);
      }
    }

    static std::string ConvertState(int state) {
      switch (state) {
      case 1:return "OFFLINE";
      case 2:return "ONLINE";
      case 3:return "STARTING";
      case 4:return "STOPPING";
      case 5:return "START_FAILED";
      case 6:return "STOP_FAILED";
      default:return "OFFLINE";
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
    friend std::ostream &operator<<(std::ostream &os, const ListServerResponse &r) {
      os << "ListServerResponse={region='" << r.region << "' nextToken='" << r.nextToken << "' servers={'";
      for (auto &server : r.servers) {
        os << server.ToString();
      }
      return os;
    }
  };

} // namespace AwsMock::Dto::Transfer

#endif // AWSMOCK_DTO_TRANSFER_LISTSERVERRESPONSE_H
