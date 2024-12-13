//
// Created by vogje01 on 13/08/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_VERSION_RESPONSE_H
#define AWSMOCK_DTO_DOCKER_VERSION_RESPONSE_H

// C++ includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/dto/docker/model/Platform.h>

namespace AwsMock::Dto::Docker {

    /**
     * Docker details
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Details {

        /**
         * API version
         */
        std::string apiVersion;

        /**
         * Architecture
         */
        std::string architecture;

        /**
         * Build time
         */
        system_clock::time_point buildTime;

        /**
         * Experimental
         */
        bool experimental = false;

        /**
         * Git commit userPoolId
         */
        std::string gitCommit;

        /**
         * @brief Deserialize from a JSON object
         *
         * @param document JSON object
         */
        void FromDocument(const view_or_value<view, value> &document) {

            try {
                apiVersion = Core::Bson::BsonUtils::GetStringValue(document, "ApiVersion");
                architecture = Core::Bson::BsonUtils::GetStringValue(document, "Arch");
                buildTime = Core::Bson::BsonUtils::GetDateValue(document, "BuildTime");
                experimental = Core::Bson::BsonUtils::GetBoolValue(document, "Experimental");
                gitCommit = Core::Bson::BsonUtils::GetStringValue(document, "GitCommit");

            } catch (bsoncxx::exception &exc) {
                log_error << exc.what();
                throw Core::ServiceException(exc.what());
            }
        }
    };

    /**
     * Docker component
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Component {

        /**
         * Platform name
         */
        std::string name;

        /**
         * Version
         */
        std::string version;

        /**
         * Details
         */
        Details details;

        /**
         * @brief Deserialize from a JSON object
         *
         * @param document JSON object
         */
        void FromDocument(const view_or_value<view, value> &document) {

            try {

                name = Core::Bson::BsonUtils::GetStringValue(document, "Name");
                version = Core::Bson::BsonUtils::GetStringValue(document, "Version");

                if (document.view().find("Details") != document.view().end()) {
                    details.FromDocument(document.view()["Details"].get_document().value);
                }

            } catch (bsoncxx::exception &exc) {
                log_error << exc.what();
                throw Core::JsonException(exc.what());
            }
        }
    };

    /**
     * Docker version
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct DockerVersion {

        /**
         * Platform object
         */
        Platform platform;

        /**
         * Components
         */
        std::vector<Component> components;

        /**
         * Deserialize from a JSON object
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString) {

            try {

                const value document = bsoncxx::from_json(jsonString);

                // Platform
                if (document.view().find("Platform") != document.view().end()) {
                    platform.FromDocument(document.view()["Platform"].get_document().value);
                }

                // Components
                if (document.view().find("Components") != document.view().end()) {
                    for (const bsoncxx::array::view jsonArray = document.view()["Components"].get_array().value; const auto &jsonComponent: jsonArray) {
                        Component component;
                        component.FromDocument(jsonComponent.get_document().value);
                        components.push_back(component);
                    }
                }

            } catch (bsoncxx::exception &exc) {
                log_error << exc.what();
                throw Core::JsonException(exc.what());
            }
        }
    };

}// namespace AwsMock::Dto::Docker

#endif// AWSMOCK_DTO_DOCKER_VERSION_RESPONSE_H
