//
// Created by vogje01 on 4/12/24.
//

#ifndef AWSMOCK_CORE_TASK_H
#define AWSMOCK_CORE_TASK_H

// C++ standard includes
#include <future>
#include <iostream>
#include <thread>
#include <utility>

// AwsMock includes
#include <awsmock/core/LogStream.h>

namespace AwsMock::Core {

    /**
   * Task class
   *
   * @author jens.vogt@opitz-consulting.com
   */
    class Task {

      public:
        /**
       * Constructor
       *
       * @param name task name
       * @param timeout timeout in milliseconds
       */
        explicit Task(std::string name, int timeout) : _name(name), _timeout(timeout) {}

        /**
       * Start the task
       */
        void Start();

        /**
       * Stop the task
       */
        void Stop();

        /**
       * Main loop
       */
        virtual void Initialize() = 0;

        /**
       * Main loop
       */
        virtual void Run() = 0;

      private:
        /**
       * Logger
       */
        Core::LogStream _logger;

        /**
       * Timer name
       */
        std::string _name;

        /**
       * Loop timeout
       */
        int _timeout;

        /**
       * Promise for stopping thread
       */
        std::promise<void> _stop;

        /**
       * Thread handle
       */
        std::future<void> _thread_handle;
    };
}// namespace AwsMock::Core

#endif//AWSMOCK_CORE_TASK_H
