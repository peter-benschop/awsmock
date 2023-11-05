//
// Created by vogje01 on 07/09/2023.
//

#ifndef AWSMOCK_CORE_TESTUTILS_H
#define AWSMOCK_CORE_TESTUTILS_H

// C++ includes
#include <string>
#include <fstream>

// AwsMock includes
#include <awsmock/core/SystemUtils.h>

#define TMP_PROPERTIES_FILE "/tmp/aws-mock.properties"

namespace AwsMock::Core {

  class TestUtils {

    public:

      /**
       * Creates a test configuration file
       */
      static void CreateTestConfigurationFile();

  };
}
#endif //AWSMOCK_CORE_TESTUTILS_H
