//
// Created by vogje01 on 4/12/24.
//

#include <awsmock/core/Task.h>

namespace AwsMock::Core {

  Task::Task(std::string name, int timeout) : _logger(Poco::Logger::get("Timer")), _name(std::move(name)), _timeout(timeout) {

  }

  void Task::Start() {

    log_debug << "Timer starting, name: " << _name;

    Initialize();
    log_debug << "Timer initialized, name: " << _name;

    auto future = std::shared_future<void>(_stop.get_future());
    _thread_handle = std::async(std::launch::async, [future, this]() {

      std::future_status status;
      do {
        status = future.wait_for(std::chrono::seconds(_timeout));
        if (status == std::future_status::timeout) {

          Run();

        } else if (status == std::future_status::ready) {

          log_debug << "Timer stopped, name: " << _name;

        }
      } while (status != std::future_status::ready);
    });
  }

  void Task::Stop() {
    _stop.set_value();
  }
}