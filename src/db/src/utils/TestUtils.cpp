//
// Created by vogje01 on 23/07/2023.
//

#include <awsmock/utils/TestUtils.h>

namespace AwsMock::Database {

  std::vector<std::string> TestUtils::_services = {"s3", "sqs", "sns", "lambda", "transfer"};

  void TestUtils::CreateServices() {
    Core::Configuration configuration = Core::Configuration(TMP_PROPERTIES_FILE);
    auto _serviceDatabase = ModuleDatabase(configuration);
    for (const auto &it : _services) {
      _serviceDatabase.CreateOrUpdateModule({.oid={}, .name=it, .status=Entity::Module::ModuleStatus::RUNNING});
    }
  }
}