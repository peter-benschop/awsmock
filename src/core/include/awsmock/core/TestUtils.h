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
#include <awsmock/core/Configuration.h>

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

    /**
     * Returns the name of the generated test configuration properties file.
     *
     * @return name of the generated test configuration file
     */
    static std::string GetTestConfigurationFilename();

    /**
     * Returns the name of the generated test configuration properties file.
     *
     * @param withDatabase run with MongoDB database
     * @return name of the generated test configuration file
     */
    static Core::Configuration GetTestConfiguration(bool withDatabase = true);

    /**
     * Send a CLI command
     *
     * @param service service name
     * @param command command name
     * @return exec result
     */
    static Core::ExecResult SendCliCommand(const std::string &service, const std::string &command);
  };
}
#endif //AWSMOCK_CORE_TESTUTILS_H
