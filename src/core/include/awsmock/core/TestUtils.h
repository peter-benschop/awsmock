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
     * Creates a test configuration file.
     *
     * <p>Database will be switched off.</p>
     */
    static void CreateTestConfigurationFile();

    /**
     * Creates a test configuration file.
     *
     * @param withDatabase set to true when the configuration should be for a database
     */
    static void CreateTestConfigurationFile(bool withDatabase);

  };
}
#endif //AWSMOCK_CORE_TESTUTILS_H
