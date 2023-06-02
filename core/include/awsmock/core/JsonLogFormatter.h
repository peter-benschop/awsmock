//
// Created by vogje01 on 05/01/2023.
//

#ifndef AWSMOCK_CORE_JSONLOGFORMATTER_H
#define AWSMOCK_CORE_JSONLOGFORMATTER_H

// Poco includes
#include "Poco/Formatter.h"
#include "Poco/Message.h"
#include <Poco/JSON/Object.h>
#include "Poco/Net/DNS.h"

namespace AwsMock::Core {

    static const std::string PRIORITY_STR_FATAL = "FATAL";
    static const std::string PRIORITY_STR_CRITIAL = "CRITICAL";
    static const std::string PRIORITY_STR_ERROR = "ERROR";
    static const std::string PRIORITY_STR_WARNING = "WARNING";
    static const std::string PRIORITY_STR_NOTICE = "NOTICE";
    static const std::string PRIORITY_STR_INFORMATION = "INFO";
    static const std::string PRIORITY_STR_DEBUG = "DEBUG";
    static const std::string PRIORITY_STR_TRACE = "TRACE";

    /**
     * JSON log formatter.
     * <p>
     * This formatter s used to generate JSON output for all log messages, which ic needed by the Libri Kibana implementation.
     * </p>
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class JsonLogFormatter : public Poco::Formatter {
    public:
        /**
         * Default constructor
         */
        JsonLogFormatter();

        /**
         * Default destructor
         */
        ~JsonLogFormatter();

        /**
         * Format the message.
         *
         * @param msg logging message
         * @param text JSON string of message
         */
        void format(const Poco::Message &msg, std::string &text);

        /**
         * Sets an additional property.
         *
         * @param name name of the property
         * @param value value of the property
         */
        void setProperty(const std::string &name, const std::string &value);

        /**
         * Returns an additional property.
         *
         * @param name name of the property
         * @return value of the property
         */
        std::string getProperty(const std::string &name) const;

    private:
        /**
         * Map of additional properties as key/value pairs
         */
        std::map<std::string, std::string> _properties;

        /**
         * Converts the logger ENUM priority to string.
         *
         * @param p ENUM priority
         * @return string representation
         */
        static std::string priorityToString(Poco::Message::Priority p);

        /**
         * Returns the normalised filename.
         *
         * @param filename filename to parse
         * @return normalized file name.
         */
        std::string getFilename(const std::string &filename);
    };
}
#endif // AWSMOCK_CORE_JSONLOGFORMATTER_H
