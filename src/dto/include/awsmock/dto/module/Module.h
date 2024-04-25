//
// Created by vogje01 on 10/23/23.
//

#ifndef AWSMOCK_DTO_MODULE_MODULE_H
#define AWSMOCK_DTO_MODULE_MODULE_H

// C++ includes
#include <string>

// AwsMock includes
#include "awsmock/core/JsonUtils.h"
#include <awsmock/core/JsonException.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/module/Module.h>
#include <awsmock/entity/module/ModuleState.h>

namespace AwsMock::Dto::Module {

    struct Module {

        /**
     * Name
     */
        std::string name;

        /**
     * Status
     */
        Database::Entity::Module::ModuleState status;

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
        Poco::DateTime modified = Poco::DateTime();
        ;

        /**
     * Convert to JSON representation
     *
     * @param moduleEntity module entity
     * @return JSON string
     */
        [[nodiscard]] std::string ToJson() const;

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

}// namespace AwsMock::Dto::Module

#endif// AWSMOCK_DTO_MODULE_MODULE_H
