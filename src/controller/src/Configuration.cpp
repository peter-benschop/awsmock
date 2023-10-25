//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/controller/Configuration.h>

namespace AwsMock::Controller {

    Configuration::Configuration() : Core::Configuration() {
        InitializeConfig();
    }

    Configuration::Configuration(const std::string &basename) : Core::Configuration(basename) {
        InitializeConfig();
    }

    void Configuration::InitializeConfig() {
    }

} // namespace AwsMock