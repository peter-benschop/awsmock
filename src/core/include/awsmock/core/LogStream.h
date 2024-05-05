//
// Created by vogje01 on 20/06/2023.
//

#ifndef AWS_MOCK_CORE_LOG_STREAM_H
#define AWS_MOCK_CORE_LOG_STREAM_H

// C++ standard includes
#include <filesystem>
#include <iostream>
#include <istream>
#include <string_view>

// Plog includes
#define PLOG_OMIT_LOG_DEFINES
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Log.h>


namespace AwsMock::Core {

    /**
     * Logging setup
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class LogStream {

      public:

        /**
         * Constructor
         */
        LogStream();

        /**
         * Constructor
         *
         * @param severity PLog severity string
         */
        explicit LogStream(const std::string &severity);
    };

}// namespace AwsMock::Core

#define log_fatal PLOG_FATAL
#define log_error PLOG_ERROR
#define log_warning PLOG_WARNING
#define log_info PLOG_INFO
#define log_debug PLOG_DEBUG
#define log_trace PLOG_VERBOSE

#endif// AWS_MOCK_CORE_LOG_STREAM_H
