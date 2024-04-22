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

// Poco includes
#include <Poco/Logger.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>

namespace AwsMock::Core {

  /**
   * General asynchronous job execution class
   *
   * @author jens.vogt@opitz-consulting.com
   */
  class Timer {

    public:

      /**
       * Constructor
       *
       * @param name timer name
       * @param timeout timeout in seconds
       */
      explicit Timer(std::string name, int timeout) : _name(std::move(name)), _timeout(timeout) {}

      /**
       * Constructor
       *
       * @param name timer name
       */
      explicit Timer(std::string name) : _name(std::move(name)) {}

      /**
       * Start the task
       */
      void Start();

      /**
       * Start the task
       */
      void Start(int timeout);

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

      /**
       * Shutdown
       */
      virtual void Shutdown() = 0;

    private:

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
}

#endif //AWSMOCK_CORE_TASK_H
