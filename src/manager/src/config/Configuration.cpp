//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/config/Configuration.h"

namespace AwsMock {

  Configuration::Configuration() : Core::Configuration() {
    InitializeConfig();
  }

  Configuration::Configuration(const std::string &basename) : Core::Configuration(basename) {
    InitializeConfig();
  }

  void Configuration::InitializeConfig() {
    // Data directory
    DefineProperty("awsmock.data.dir", "AWSMOCK_DATA_DIR", "/home/awsmock/data");

    // Thread pool
    DefineProperty("awsmock.threadpool.min", "AWSMOCK_THREADPOOL_MIN", "4");
    DefineProperty("awsmock.threadpool.max", "AWSMOCK_THREADPOOL_MAX", "32");
    DefineProperty("awsmock.threadpool.idletime", "AWSMOCK_THREADPOOL_MAX_IDLETIME", "60");
  }

} // namespace AwsMock