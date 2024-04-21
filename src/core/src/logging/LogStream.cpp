
#include <iostream>
#include <utility>
#include "awsmock/core/LogStream.h"

namespace AwsMock::Core {

    LogStream::LogStream() {
        plog::init<plog::TxtFormatter>(plog::verbose, plog::streamStdOut);
    }

    LogStream::LogStream(const std::string& severity) {
        plog::init<plog::TxtFormatter>(plog::severityFromString(severity.c_str()), plog::streamStdOut);
    }

} // namespace AwsMock::Core
