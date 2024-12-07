//
// Created by vogje01 on 13/08/2023.
//

#ifndef AWSMOCK_DTO_DOCKER_VERSION_RESPONSE_H
#define AWSMOCK_DTO_DOCKER_VERSION_RESPONSE_H

// C++ includes
#include <sstream>
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/exception/ServiceException.h>

namespace AwsMock::Dto::Docker {

    /**
     * Docker platform
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Platform {

        /**
         * Platform name
         */
        std::string name;

        /**
         * Deserialize from a JSON object
         *
         * @param jsonObject JSON object
         */
        void FromJson(const Poco::JSON::Object::Ptr &jsonObject) {

            try {
                Core::JsonUtils::GetJsonValueString("Name", jsonObject, name);
            } catch (Poco::Exception &exc) {
                std::cerr << exc.message() << std::endl;
                throw Core::ServiceException(exc.message());
            }
        }
    };

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
        Poco::DateTime buildTime;

        /**
         * Experimental
         */
        bool experimental = false;

        /**
         * Git commit userPoolId
         */
        std::string gitCommit;

        /**
         * Deserialize from a JSON object
         *
         * @param jsonObject JSON object
         */
        void FromJson(Poco::JSON::Object::Ptr jsonObject) {

            try {
                Core::JsonUtils::GetJsonValueString("ApiVersion", jsonObject, apiVersion);
                Core::JsonUtils::GetJsonValueString("Arch", jsonObject, architecture);
                Core::JsonUtils::GetJsonValueDate("BuildTime", jsonObject, buildTime);
                Core::JsonUtils::GetJsonValueBool("Experimental", jsonObject, experimental);
                Core::JsonUtils::GetJsonValueString("GitCommit", jsonObject, gitCommit);

            } catch (Poco::Exception &exc) {
                std::cerr << exc.message() << std::endl;
                throw Core::ServiceException(exc.message());
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
         * Deserialize from a JSON object
         *
         * @param jsonObject JSON object
         */
        void FromJson(Poco::JSON::Object::Ptr jsonObject) {

            try {
                Core::JsonUtils::GetJsonValueString("Name", jsonObject, name);
                Core::JsonUtils::GetJsonValueString("Version", jsonObject, version);
                if (jsonObject->has("Details")) {
                    details.FromJson(jsonObject->getObject("Details"));
                }

            } catch (Poco::Exception &exc) {
                std::cerr << exc.message() << std::endl;
                throw Core::ServiceException(exc.message());
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
            }
        }
    };

}// namespace AwsMock::Dto::Docker

#endif// AWSMOCK_DTO_DOCKER_VERSION_RESPONSE_H
