//
// Created by vogje01 on 22/08/2022.
//

#ifndef AWSMOCK_CONTROLLER_CONFIGURATION_H
#define AWSMOCK_CONTROLLER_CONFIGURATION_H

// Standard C++ includes
#include <string>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>

#define CONFIGURATION_BASE_PATH std::string("/etc/awsmock.properties")

namespace AwsMock::Controller {

    /**
     * AwsMock controller configuration
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class Configuration : public Core::Configuration {

      public:
        /**
         * Constructor
         */
        Configuration();

        /**
         * Constructor.
         *
         * @param basename base name of the configuration file.
         */
        explicit Configuration(const std::string &basename);

        /**
         * Initialize the configuration and add the default configuration options.
         */
        void InitializeConfig();
    };

}// namespace AwsMock::Controller

#endif//AWSMOCK_CONTROLLER_CONFIGURATION_H
