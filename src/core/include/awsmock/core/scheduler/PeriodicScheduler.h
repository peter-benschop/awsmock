//
// Created by vogje01 on 10/7/24.
//

#ifndef AWSMOCK_CORE_PERIODIC_SCHEDULER_H
#define AWSMOCK_CORE_PERIODIC_SCHEDULER_H

// C++ includes
#include <chrono>
#include <functional>
#include <string>

// Boost includes
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <utility>

// AwsMOck includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/scheduler/PeriodicTask.h>

namespace AwsMock::Core {

    using std::chrono::system_clock;

    class PeriodicScheduler : boost::noncopyable {

      public:

        /**
        * @brief Singleton instance
        */
        static PeriodicScheduler &instance() {
            static PeriodicScheduler monitoringDatabase;
            return monitoringDatabase;
        }

        /**
        * Main routine
        */
        void Run() {
            io_service.run();
        }

        /**
         * @brief Add a task to the scheduler.
         *
         * @param name name of the task
         * @param task task function
         * @param interval interval in seconds
         * @param startTime time for the first execution (should be something like (00:00, oder 04:00)
         */
        void AddTask(std::string const &name, PeriodicTask::handler_fn const &task, int interval, int delay = 0) {
            tasks.push_back(std::make_unique<PeriodicTask>(std::ref(io_service), name, interval, task, delay));
        }

        /**
         * @brief Shutdown the scheduler
         */
        void Shutdown() {
            io_service.stop();
        };

      private:

        /**
         * Boost asio IO service
         */
        boost::asio::io_service io_service;

        /**
         * Task list
         */
        std::vector<std::unique_ptr<PeriodicTask>> tasks;
    };

}// namespace AwsMock::Core

#endif//AWSMOCK_CORE_PERIODIC_SCHEDULER_H
