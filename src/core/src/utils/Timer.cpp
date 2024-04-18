//
// Created by vogje01 on 4/12/24.
//

#include <awsmock/core/Timer.h>

namespace AwsMock::Core {

  Timer::Timer(std::string name, int timeout) : _logger(Poco::Logger::get("Timer")), _name(std::move(name)), _timeout(timeout) {

  }

  void Timer::Start() {

    log_debug_stream(_logger) << "Timer starting, name: " << _name << std::endl;

    Initialize();
    log_debug_stream(_logger) << "Timer initialized, name: " << _name << std::endl;

    auto future = std::shared_future<void>(_stop.get_future());
    _thread_handle = std::async(std::launch::async, [future, this]() {

      std::future_status status;
      do {
        status = future.wait_for(std::chrono::seconds(_timeout));
        if (status == std::future_status::timeout) {

          Run();

        } else if (status == std::future_status::ready) {

          log_debug_stream(_logger) << "Timer stopped, name: " << _name << std::endl;

        }
      } while (status != std::future_status::ready);
    });
  }

  void Timer::Stop() {
    _stop.set_value();
  }
}