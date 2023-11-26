//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITOSERVICE_H
#define AWSMOCK_SERVICE_COGNITOSERVICE_H

// C++ standard includes
#include <string>

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

// AwsMock includes
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/ServiceException.h>
#include "awsmock/dto/cognito/CreateUserPoolRequest.h"
#include "awsmock/dto/cognito/CreateUserPoolResponse.h"
#include "awsmock/dto/cognito/DeleteUserPoolRequest.h"
#include <awsmock/dto/cognito/ListUserPoolRequest.h>
#include <awsmock/dto/cognito/ListUserPoolResponse.h>
#include <awsmock/repository/CognitoDatabase.h>

#define DEFAULT_DATA_DIR  "/tmp/awsmock/data"
#define DEFAULT_S3_DATA_DIR  "/tmp/awsmock/data/s3"

namespace AwsMock::Service {

  class CognitoService {

  public:

    /**
     * Constructor
     *
     * @param configuration module configuration
     */
    explicit CognitoService(Core::Configuration &configuration);

    /**
     * Create a new cognito user pool
     *
     * @param request create user pool request
     * @return CreateUserPoolRequest DTO
     */
    Dto::Cognito::CreateUserPoolResponse CreateUserPool(const Dto::Cognito::CreateUserPoolRequest &request);

    /**
     * List cognito user pools
     *
     * @param request list user pool request
     * @return ListUserPoolResponse DTO
     */
    Dto::Cognito::ListUserPoolResponse ListUserPools(const Dto::Cognito::ListUserPoolRequest &request);

    /**
     * Delete a cognito user pool
     *
     * @param request delete user pool request
     */
    void DeleteUserPool(const Dto::Cognito::DeleteUserPoolRequest &request);

  private:

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Configuration
     */
    Core::Configuration &_configuration;

    /**
     * Database connection
     */
    std::unique_ptr<Database::CognitoDatabase> _database;

    /**
     * S3 account id
     */
    std::string _accountId;
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_COGNITOSERVICE_H
