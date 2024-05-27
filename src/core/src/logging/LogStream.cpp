
#include <awsmock/core/LogStream.h>

namespace AwsMock::Core {

    void LogStream::Initialize() {
        plog::init<LogFormatter>(plog::error, plog::streamStdOut);
    }

    void LogStream::SetSeverity(const std::string &severity) {
        plog::get()->setMaxSeverity(plog::severityFromString(severity.c_str()));
    }

    void LogStream::SetFilename(const std::string &filename) {
        static plog::RollingFileAppender<LogFormatter> fileAppender(filename.c_str(), 10 * 1024 * 1024, 5);
        plog::get()->addAppender(&fileAppender);
    }

}// namespace AwsMock::Core