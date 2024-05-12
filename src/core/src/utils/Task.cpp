//
// Created by vogje01 on 4/12/24.
//

#include <awsmock/core/Task.h>

namespace AwsMock::Core {

    Task::Task(std::string name) : _name(std::move(name)) {
    }

    void Task::DoWork() {

        log_debug << "Task starting, name: " << _name;
        Run();
    }

}// namespace AwsMock::Core