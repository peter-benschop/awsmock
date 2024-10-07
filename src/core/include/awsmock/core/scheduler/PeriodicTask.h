//
// Created by vogje01 on 10/7/24.
//

#ifndef AWSMOCK_CORE_PERIODIC_TASK_H
#define AWSMOCK_CORE_PERIODIC_TASK_H

// C++ includes
#include <functional>
#include <string>
#include <utility>

// Boost includes
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/noncopyable.hpp>

// AwsMOck includes
#include <awsmock/core/LogStream.h>

namespace AwsMock::Core {

    class PeriodicTask : boost::noncopyable {

      public:

        typedef std::function<void()> handler_fn;

        PeriodicTask(boost::asio::io_service &ioService, std::string const &name, int interval, handler_fn task, int delay)
            : ioService(ioService), interval(interval), task(std::move(task)), name(name), timer(ioService), _delay(delay) {
            log_debug << "Create PeriodicTask '" << name << "'";

            // Schedule start to be run by the io_service
            ioService.post([this] { start(); });
        }

        void execute(boost::system::error_code const &e) {

            if (e != boost::asio::error::operation_aborted) {

                log_debug << "Execute PeriodicTask '" << name << "'";

                task();

                timer.expires_at(timer.expires_at() + boost::posix_time::seconds(interval));
                start_wait();
            }
        }

        void start() {
            log_debug << "Start PeriodicTask '" << name << "'";

            // Wait for first execution time
            if (_delay > 0) {
                //                std::this_thread::sleep_for(std::chrono::seconds(_delay));
            }

            // Uncomment if you want to call the handler on startup (i.e. at time 0)
            task();

            timer.expires_from_now(boost::posix_time::seconds(interval));
            start_wait();
        }

      private:

        void start_wait() {
            timer.async_wait(boost::bind(&PeriodicTask::execute, this, boost::asio::placeholders::error));
        }

      private:

        boost::asio::io_service &ioService;
        boost::asio::deadline_timer timer;
        handler_fn task;
        std::string name;
        int interval;
        int _delay;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_PERIODIC_TASK_H
