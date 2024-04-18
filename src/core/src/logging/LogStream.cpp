
#include <iostream>
#include <utility>
#include "awsmock/core/LogStream.h"

namespace AwsMock::Core {

  PLogStream::PLogStream() {
    plog::init<plog::TxtFormatter>(plog::verbose, plog::streamStdOut);
  }

} // namespace AwsMock::Core
