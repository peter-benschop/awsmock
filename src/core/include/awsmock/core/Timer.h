//
// Created by vogje01 on 4/12/24.
//

#ifndef AWSMOCK_CORE_TIMER_H
#define AWSMOCK_CORE_TIMER_H

// C++ standard includes
#include <iostream>
#include <stop_token>
#include <thread>


// AwsMock includes
#include <awsmock/core/LogStream.h>

namespace AwsMock::Core {

    /**
     * @brief General asynchronous job execution class
     *
     * This is supposed to stop immediately, in case a stop signal is send to the thread.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Timer {

      public:

        /**
         * @brief Constructor
         *
         * @param name timer name
         * @param timeout timeout in seconds
         */
        explicit Timer(std::string name, int timeout) : _name(std::move(name)), _timeout(timeout) {}

        /**
         * @brief Constructor
         *
         * @param name timer name
         */
        explicit Timer(std::string name) : _name(std::move(name)) {}

        /**
         * @brief Start the timer
         */
        virtual void Start();

        /**
         * @brief Start the task
         */
        void Start(int timeout);

        /**
         * @brief Restart the timer
         */
        void Restart();

        /**
         * @brief Stop the task
         */
        void Stop();

        /**
         * @brief Initialization
         */
        virtual void Initialize() = 0;

        /**
         * @brief Main loop
         */
        virtual void Run() = 0;

        /**
         * @brief Shutdown
         */
        virtual void Shutdown() = 0;

        /**
         * @brief Sets the timeout.
         *
         * <p>
         * The time will be stopped and restarted
         * </p>
         */
        void SetTimeout(int timeout);

        /**
         * @brief Thread main method.
         *
         * @param stopSource stop source variable
         */
        void DoWork(const std::stop_source &stopSource);

      private:

        /**
         * Timer name
         */
        std::string _name;

        /**
         * Loop timeout
         */
        int _timeout{};

        /**
         * Stop source
         */
        std::stop_source _stopSource;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_TIMER_H
