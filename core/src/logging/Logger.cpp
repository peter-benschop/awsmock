//
// Created by vogje01 on 05/01/2023.
//

#include "awsmock/core/Logger.h"

namespace AwsMock::Core {

    const std::string Logger::DEFAULT_LOG_PATTERN = "%d-%m-%Y %H:%M:%S.%i [%p] %I %s:%u - %t";

    Logger::Logger() {
        SetDefaultConsoleLogger();
    }

    Logger::Logger(const std::string &profile) {
        SetProfile(profile);
    }

    void Logger::SetDefaultConsoleLogger() {
        Poco::AutoPtr<Poco::ConsoleChannel> pCons(new Poco::ConsoleChannel);
        Poco::AutoPtr<Poco::PatternFormatter> pPF(new Poco::PatternFormatter(DEFAULT_LOG_PATTERN));
        Poco::AutoPtr<Poco::FormattingChannel> pFC(new Poco::FormattingChannel(pPF, pCons));
        Poco::Logger::root().setChannel(pFC);
    }

    void Logger::SetJsonConsoleLogger() {
        Poco::AutoPtr<Poco::ConsoleChannel> pCons(new Poco::ConsoleChannel);
        Poco::AutoPtr<JsonLogFormatter> pPF(new JsonLogFormatter());
        Poco::AutoPtr<Poco::FormattingChannel> pFC(new Poco::FormattingChannel(pPF, pCons));
        Poco::Logger::root().setChannel(pFC);
    }

    void Logger::SetProfile(const std::string &profile) {
        if(profile == "localstack") {
            SetDefaultConsoleLogger();
        } else {
            SetJsonConsoleLogger();
        }
    }

    void Logger::SetLogLevel(const std::string &logLevel) {
        Poco::Logger::root().setLevel(logLevel);
    }
}