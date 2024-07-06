//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_LAMBDA_WORKER_H
#define AWSMOCK_SERVICE_LAMBDA_WORKER_H

// AwsMock includes
#include <awsmock/core/Timer.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/service/docker/DockerService.h>

#define DEFAULT_LAMBDA_LIFETIME 60

namespace AwsMock::Service {

    /**
     * @brief Lambda worker thread
     *
     * Used as background thread to do maintenance work, like removing expired lambda instances.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class LambdaWorker : public Core::Timer {

      public:

        /**
         * @brief Constructor
         */
        explicit LambdaWorker(int timeout) : Core::Timer("lambda-worker", timeout) {}

        /**
         * @brief Initialization
         */
        void Initialize() override;

        /**
         * @brief Main method
         */
        void Run() override;

        /**
         * @brief Shutdown
         */
        void Shutdown() override;

      private:

        /**
         * @brief Remove expired lambda functions
         *
         * @par
         * Loops over all lambda functions and removes the lambda container, when the lambdas are expired.
         */
        [[maybe_unused]] void RemoveExpiredLambdas();

        /**
         * Database connection
         */
        Database::LambdaDatabase &_lambdaDatabase = Database::LambdaDatabase::instance();

        /**
         * Docker service
         */
        DockerService &_dockerService = DockerService::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_LAMBDA_WORKER_H
