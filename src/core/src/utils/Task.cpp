//
// Created by vogje01 on 4/12/24.
//

#include <awsmock/core/Task.h>

namespace AwsMock::Core {

    void Task::Start() {

        log_debug << "Task starting, name: " << _name;

        Initialize();
        log_debug << "Task initialized, name: " << _name;

        auto future = std::shared_future<void>(_stop.get_future());
        _thread_handle = std::async(std::launch::async, [future, this]() {
            Run();
            future.get();
        });
    }

    void Task::Stop() {
        _stop.set_value();
    }
}// namespace AwsMock::Core