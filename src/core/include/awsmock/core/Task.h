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
     * @brief Task class
     *
     * A task is a one-shot asynchronously running thread. The implementing class should define two methods: "Run()" and "Initialize()". Initialize
     * should do all the initial initialization, whereas Run() does the work. The thread is automatically stopped and cleaned up.
     *
     * @code{.cpp}
     * Core::Task DoSomethingAsynchron();
     * DoSomethingAsynchron.Start();
     *
     * class DoSomethingAsynchron {
     *
     *   Initialize() {
     *   ...
     *   }
     *
     *   Run() {
     *   ...
     *   }
     * }
     * @endcode
     * @author jens.vogt\@opitz-consulting.com
     */
    class Task {

      public:

        /**
         * @brief Constructor
         *
         * @param name task name
         */
        explicit Task(std::string name);

        /**
         * @brief Main loop
         */
        virtual void Run() = 0;

        /**
         * @brief Actually do the work. WIll call Run method.
         */
        [[maybe_unused]] void DoWork();

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
         * Stop source
         */
        std::stop_source _stopSource;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_TASK_H
