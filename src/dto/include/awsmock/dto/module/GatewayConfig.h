//
// Created by vogje01 on 10/23/23.
//

#ifndef AWSMOCK_DTO_MODULE_GATEWAYCONFIG_H
#define AWSMOCK_DTO_MODULE_GATEWAYCONFIG_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPServerResponse.h>

// AwsMock includes
#include "awsmock/core/JsonUtils.h"
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::Module {

  struct GatewayConfig {

    /**
     * Default region
     */
    std::string region;

    /**
     * Endpoint
     */
    std::string endpoint;

    /**
     * Protocol
     */
    std::string protocol = "http";

    /**
     * Host
     */
    std::string host = "localhost";

    /**
     * Port
     */
    int port = 4566;

    /**
     * User ID
     */
    std::string user = "none";

    /**
     * Access ID
     */
    std::string accessId = "000000000000";

    /**
     * Client ID
     */
    std::string clientId = "000000000000";

    /**
     * Data directory
     */
    std::string dataDir = "/tmp/awsmock/data";

    /**
     * Pretty print
     */
    bool prettyPrint = false;

    /**
     * Database active
     */
    bool databaseActive = false;

    /**
     * Convert to JSON representation
     *
     * @param moduleEntity module entity
     * @return JSON string
     */
    static std::string ToJson(const GatewayConfig &gatewayConfig);

    /**
     * Convert from JSON representation
     *
     * @param payload JSON representation
     * @return GatewayConfig
     */
    static GatewayConfig FromJson(const std::string &payload);

    /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] std::string ToString() const;

    /**
     * Stream provider.
     *
     * @param os output stream
     * @param m module struct
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const GatewayConfig &m);

  };

} // namespace AwsMock::Dto

#endif // AWSMOCK_DTO_MODULE_GATEWAYCONFIG_H
