//
// Created by vogje01 on 07/09/2023.
//

#ifndef AWSMOCK_DB_TESTUTILS_H
#define AWSMOCK_DB_TESTUTILS_H

// C++ includes
#include <string>
#include <fstream>
#include <vector>

// AwsMock includes
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/ServiceDatabase.h>
#include <awsmock/entity/service/ServiceStatus.h>

namespace AwsMock::Database {

  class TestUtils {

    public:

      /**
       * Creates all services in the service database
       */
      static void CreateServices();

      /**
      * Service names
      */
      static std::vector<std::string> _services;
  };

} //namespace AwsMock::Database

#endif // AWSMOCK_DB_TESTUTILS_H
