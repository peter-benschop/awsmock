//
// Created by vogje01 on 4/12/24.
//

#include <awsmock/core/JTimer.h>

namespace AwsMock::Core {

    void JTimer::Start(int timeout) {
        _timeout = timeout;
        Start();
    }

    void JTimer::Start() {

        log_debug << "Timer starting, name: " << _name << " timeout: " << _timeout;

        Initialize();
        log_debug << "Timer initialized, name: " << _name;

        _thread = std::jthread(&JTimer::DoWork, this, _stopSource);
    }

    void JTimer::DoWork(std::stop_source stopSource) {
        std::stop_token stoken = stopSource.get_token();
        thread_local int i = 0;
        while (!stoken.stop_requested()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (i >= _timeout) {
                Run();
                i = 0;
            }
            i++;
        }
        log_debug << "Timer stopped, name: " << _name << ". Starting shutdown.";
        Shutdown();
        log_debug << "Shutdown finished, name: " << _name;
    }

    void JTimer::Restart() {
        Stop();
        Start();
        log_info << "Timer restarted, name: " << _name << " timeout: " << _timeout;
    }

    void JTimer::SetTimeout(int timeout) {
        _timeout = timeout;
        Restart();
    }

    void JTimer::Stop() {
        log_debug << "Timer stop requested, name: " << _name << ". Starting shutdown.";
        _stopSource.request_stop();
        _thread.join();
    }
}// namespace AwsMock::Core