//
// Created by vogje01 on 4/12/24.
//

#include <awsmock/core/Timer.h>

namespace AwsMock::Core {

    void Timer::Start(int timeout) {
        _timeout = timeout;
        Start();
    }

    void Timer::Start() {

        log_debug << "Timer starting, name: " << _name << " timeout: " << _timeout;

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

    void Timer::Restart() {
        Stop();
        Start();
        log_info << "Timer restarted, name: " << _name << " timeout: " << _timeout;
    }

    void Timer::SetTimeout(int timeout) {
        _timeout = timeout;
        Restart();
    }

    void Timer::Stop() {
        _stop.set_value();
    }
}