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

        std::jthread(&JTimer::DoWork, this, _stopSource).detach();
    }

    void JTimer::DoWork(const std::stop_source &stopSource) {
        std::stop_token stoken = stopSource.get_token();
        thread_local int i = 0;
        while (!stoken.stop_requested()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (stoken.stop_requested()) {
                break;
            }
            if (++i >= _timeout) {
                Run();
                i = 0;
            }
        }
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
        log_debug << "Timer shutdown requested , name: " << _name;
        Shutdown();
        _stopSource.request_stop();
        log_debug << "Timer shutdown finished, name: " << _name;
    }
}// namespace AwsMock::Core