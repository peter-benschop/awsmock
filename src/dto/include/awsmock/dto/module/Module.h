//
// Created by vogje01 on 10/23/23.
//

#ifndef AWSMOCK_DTO_MODULE_MODULE_H
#define AWSMOCK_DTO_MODULE_MODULE_H

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
#include <awsmock/entity/service/Module.h>
#include <awsmock/entity/service/ModuleStatus.h>

namespace AwsMock::Dto::Module {

  struct Module {

    /**
     * Name
     */
    std::string name;

    /**
     * Status
     */
    Database::Entity::Module::ModuleStatus status;

    /**
     * Executable
     */
    std::string executable = {};

    /**
     * HTTP port
     */
    int port = -1;

    /**
     * Creation date
     */
    Poco::DateTime created = Poco::DateTime();

    /**
     * Last modification date
     */
    Poco::DateTime modified = Poco::DateTime();;

    /**
     * Convert to JSON representation
     *
     * @param moduleEntity module entity
     * @return JSON string
     */
    static std::string ToJson(const Database::Entity::Module::Module &moduleEntity);

    /**
     * Convert to JSON representation
     *
     * @param moduleList module entity list
     * @return JSON string
     */
    static std::string ToJson(const Database::Entity::Module::ModuleList &moduleList);

    /**
     * Convert from JSON representation
     *
     * @param payload JSON representation
     * @return Module
     */
    static Module FromJson(const std::string &payload);

    /**
     * Convert from JSON representation
     *
     * @param payload JSON representation
     * @return ModuleList
     */
    static std::vector<Module> FromJsonList(const std::string &payload);

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
    friend std::ostream &operator<<(std::ostream &os, const Module &m);
  };

} // namespace AwsMock::Dto

#endif // AWSMOCK_DTO_MODULE_MODULE_H
