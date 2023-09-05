//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_WORKER_LAMBDAWORKER_H
#define AWSMOCK_WORKER_LAMBDAWORKER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/Logger.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/repository/ServiceDatabase.h>
#include <awsmock/service/S3Service.h>
#include <awsmock/worker/AbstractWorker.h>

namespace AwsMock::Worker {

    class LambdaWorker : public Poco::Runnable, public AbstractWorker {

    public:

      /**
       * Constructor
       */
      [[maybe_unused]] explicit LambdaWorker(const Core::Configuration &configuration);

      /**
       * Main method
       */
      void run() override;

    private:

      /**
       * Delete dangling, stopped containers
       */
      void CleanupContainers();

      /**
       * Start all lambdas if they are not existing
       */
      void StartLambdaFunctions();

      /**
       * Send a lambda create function request.
       *
       * @param request HTTP request
       * @param contentType HTTP content type
       */
      void SendCreateFunctionRequest(Dto::Lambda::CreateFunctionRequest &request, const std::string &contentType);

      /**
       * Returns the code from a local file.
       *
       * <p>The code will provided as a Base64 encoded zip file.</p>
       *
       * @param lambda lambda to get the code from.
       * @return Dto::Lambda::Code
       */
      Dto::Lambda::Code GetCode(const Database::Entity::Lambda::Lambda &lambda);

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Service database
       */
      std::unique_ptr<Database::ServiceDatabase> _serviceDatabase;

      /**
       * Lambda database
       */
      std::unique_ptr<Database::LambdaDatabase> _lambdaDatabase;

      /**
       * Lambda service
       */
      std::unique_ptr<Service::LambdaService> _lambdaService;

      /**
       * Docker service
       */
      std::unique_ptr<Service::DockerService> _dockerService;

      /**
       * Data dir
       */
      std::string _dataDir;

      /**
       * AWS region
       */
      std::string _region;

      /**
       * Running flag
       */
      bool _running;

      /**
       * Sleeping period in ms
       */
      int _period;

      /**
       * AWS client ID
       */
      //std::string _clientId;

      /**
       * AWS user
       */
      //std::string _user;

      /**
       * Lambda service host
       */
      std::string _lambdaServiceHost;

      /**
       * Lambda service port
       */
      int _lambdaServicePort;
    };

} // namespace AwsMock::Worker

#endif //AWSMOCK_WORKER_LAMBDAWORKER_H
