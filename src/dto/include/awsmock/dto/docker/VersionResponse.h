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

            /* Todo:
            try {
                Core::JsonUtils::GetJsonValueString("Name", jsonObject, name);
                Core::JsonUtils::GetJsonValueString("Version", jsonObject, version);
                if (jsonObject->has("Details")) {
                    details.FromJson(jsonObject->getObject("Details"));
                }

            } catch (Poco::Exception &exc) {
                std::cerr << exc.message() << std::endl;
                throw Core::ServiceException(exc.message());
            }*/
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

            /* Todo
            try {
                Poco::JSON::Parser parser;
                Poco::Dynamic::Var result = parser.parse(jsonString);
                Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

                // Platform
                if (rootObject->has("Platform")) {
                    platform.FromJson(rootObject->getObject("Platform"));
                }

                // Components
                if (rootObject->has("Components")) {
                    Poco::JSON::Array::Ptr componentsArray = rootObject->getArray("Components");
                    if (componentsArray) {
                        for (const auto &jsonComponent: *componentsArray) {
                            Component component;
                            component.FromJson(jsonComponent.extract<Poco::JSON::Object::Ptr>());
                            components.push_back(component);
                        }
                    }
                }

            } catch (Poco::Exception &exc) {
                std::cerr << exc.message() << std::endl;
                throw Core::ServiceException(exc.message());
            }*/
        }
    };

}// namespace AwsMock::Dto::Docker

#endif// AWSMOCK_DTO_DOCKER_VERSION_RESPONSE_H
