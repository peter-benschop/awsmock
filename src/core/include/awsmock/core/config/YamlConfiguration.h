//
// Created by vogje01 on 22/08/2022.
//

#ifndef AWSMOCK_CORE_YAML_CONFIGURATION_H
#define AWSMOCK_CORE_YAML_CONFIGURATION_H

// Standard C++ includes
#include <string>

// Boost includes
#include <boost/thread/mutex.hpp>

// YAML-cpp includes
#include <yaml-cpp/yaml.h>

// AwsMock includes
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/Version.h>
#include <awsmock/core/exception/CoreException.h>

namespace AwsMock::Core {
    template<typename Iter> YAML::Node lookup(const YAML::Node &node, Iter start, Iter end) {
        if (start == end) {
            return node;
        }
        return lookup(node[*start], next(start), end);
    }

    /**
     * @brief Configuration handler.
     *
     * Configuration are read from the given configuration file and can be overruled by environment variables. Supported environment variables
     * are:
     * <ul>
     * <li>AWSMOCK_COM_BASENAME: the base name of the configuration file</li>
     * <li>AWSMOCK_COM_PROFILE: the profile of the configuration file</li>
     * <li>AWSMOCK_COM_METRIC_PORT: the port for the prometheus manager (default: 9091)</li>
     * <li>AWSMOCK_COM_METRIC_TIMEOUT: the timeout for the prometheus system monitoring (default: 60000)</li>
     * <li>AWSMOCK_COM_LOGLEVEL: the logging level (default: information, possible values: debug, information, warning, error, fatal)</li>
     * </ul>
     *
     * Properties in a configuration file are key-vale pairs. The following list shows all supported keys with their default values:
     * @code{.yaml}
     * awsmock.monitoring.port=9100
     * awsmock.monitoring.timeout=60000
     * awsmock.logging.level=debug
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class YamlConfiguration {
        public:
            /**
             * @brief Constructor
             */
            YamlConfiguration();

            /**
             * @brief Singleton instance
             */
            static YamlConfiguration &instance() {
                static YamlConfiguration configuration;
                return configuration;
            }

            /**
             * @brief Constructor
             *
             * @param basename basename of the configuration file.
             */
            explicit YamlConfiguration(const std::string &basename);

            /**
             * @brief Define a new configuration property.
             *
             * <p>If the system environment has a value for the given configuration key, the environment value is set. If the configuration has already a value for the given
             * key, the key is preserved, otherwise the default value is taken. </p>
             *
             * @param key configuration key
             * @param envProperty environment variable name
             * @param defaultValue string default value
             */
            void DefineStringProperty(const std::string &key,
                                      const std::string &envProperty,
                                      const std::string &defaultValue);

            /**
             * @brief Define a new configuration property.
             *
             * <p>If the system environment has a value for the given configuration key, the environment value is set. If the configuration has already a value for the given
             * key, the key is preserved, otherwise the default value is taken. </p>
             *
             * @param key configuration key
             * @param envProperty environment variable name
             * @param defaultValue boolean default value
             */
            void DefineBoolProperty(const std::string &key, const std::string &envProperty, bool defaultValue);

            /**
             * @brief Define a new configuration property.
             *
             * <p>If the system environment has a value for the given configuration key, the environment value is set. If the configuration has already a value for the given
             * key, the key is preserved, otherwise the default value is taken. </p>
             *
             * @param key configuration key
             * @param envProperty environment variable name
             * @param defaultValue integer default value
             */
            void DefineIntProperty(const std::string &key, const std::string &envProperty, int defaultValue);

            /**
             * @brief Returns the file name of the configuration file.
             *
             * @return file name of the configuration file.
             */
            [[nodiscard]] std::string GetFilename() const;

            /**
             * @brief Sets the file name of the configuration file.
             *
             * @param filename file name of the configuration file.
             */
            void SetFilename(const std::string &filename);

            /**
             * @brief Sets a string configuration value
             *
             * @param key property key
             * @param value configuration value
             */
            void SetValue(const std::string &key, const std::string &value);

            /**
             * @brief Sets a string configuration value
             *
             * @param key property key
             * @param value configuration value
             */
            void SetValueByPath(const std::string &key, const std::string &value);

            /**
             * @brief Returns a string configuration value
             *
             * @param key property key
             * @return configuration value
             */
            [[nodiscard]] std::string GetValueString(const std::string &key);

            /**
             * @brief Returns a integer configuration value
             *
             * @param key property key
             * @return configuration value
             */
            [[nodiscard]] int GetValueInt(const std::string &key);

            /**
             * @brief Returns a integer configuration value
             *
             * @param key property key
             * @return configuration value
             */
            [[nodiscard]] long GetValueLong(const std::string &key);

            /**
             * @brief Returns a boolean configuration value
             *
             * @param key property key
             * @return configuration value
             */
            [[nodiscard]] bool GetValueBool(const std::string &key);

            /**
             * @brief Returns a boolean configuration value
             *
             * @param key property key
             * @return configuration value
             */
            [[nodiscard]] double GetValueDouble(const std::string &key);

            /**
             * @brief Sets a bool configuration value
             *
             * @param key property key
             * @param value configuration value
             */
            void SetValue(const std::string &key, bool value);

            /**
             * @brief Sets an integer configuration value
             *
             * @param key property key
             * @param value configuration value
             */
            void SetValue(const std::string &key, int value);

            /**
             * @brief Returns the application name
             *
             * @return application name
             */
            static std::string GetAppName();

            /**
             * @brief Returns the version of the library.
             *
             * @return library version
             */
            static std::string GetVersion();

            /**
             * @brief Writes the current configuration the given file
             *
             * @param filename name of the configuration file
             */
            void WriteFile(const std::string &filename) const;

            /**
             * @brief Converts the DTO to a string representation.
             *
             * @return DTO as string for logging.
             */
            [[nodiscard]] std::string ToString() const;

        private:
            /**
             * @brief Initialize the base properties
             */
            void Initialize();

            /**
             * Save the environment variables as key/value pair
             *
             * @param key environment variable key
             * @param value environment variable value
             */
            void AddToEnvList(const std::string &key, const std::string &value);

            /**
             * Reapply the environment variables to the properties, as environment variables have precedence over
             * file variables.
             */
            void ApplyEnvSettings() const;

            /**
             * @brief Checks existence of a property key
             *
             * @return true if property key exists
             */
            bool HasProperty(const std::string &key);

            /**
             * Name of the configuration file
             */
            std::string _filename;

            /**
             * Profile configuration file
             */
            std::string _profile;

            /**
             * List of defined environment variables and their value. After a configuration has been read, the environment variables need to be reapplied,
             * as environment variables have precedence over config file variables.
             */
            std::map<std::string, std::string> _envList;

            /**
             * Stream provider.
             *
             * @return output stream
             */
            friend std::ostream &operator<<(std::ostream &, const YamlConfiguration &);

            /**
              * Property mutex
              */
            static boost::mutex _configurationMutex;

            /**
             * YAML config
             */
            YAML::Node _yamlConfig;
    };
} // namespace AwsMock::Core

#endif// AWSMOCK_CORE_YAML_CONFIGURATION_H
