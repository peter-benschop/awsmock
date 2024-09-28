//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_PERFORMANCE_SERVICE_H
#define AWSMOCK_SERVICE_PERFORMANCE_SERVICE_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/dto/common/Infrastructure.h>
#include <awsmock/dto/common/Services.h>
#include <awsmock/dto/performance/GetDataRequest.h>
#include <awsmock/repository/PerformanceDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief The performance service serves basic performance data
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class PerformanceService {

      public:

        /**
         * @brief Constructor
         */
        explicit PerformanceService() : _performanceDatabase(Database::PerformanceDatabase::instance()) {};

        /**
         * @brief Return a list of performance data
         *
         * @param request get performance data request
         * @return GetDataResponse
         */
        Dto::Performance::GetDataResponse GetPerformanceData(Dto::Performance::GetDataRequest &request);

        /**
         * @brief Stops one or several modules
         *
         * @param modules module list
         * @return updated module list
         */
        Dto::Module::Module::ModuleList StopModules(Dto::Module::Module::ModuleList &modules);

        /**
         * @brief Exports the current infrastructure
         *
         * @param modules modules name list
         * @param prettyPrint JSON pretty print, if true JSON indent = 4
         * @param includeObjects include objects in the export
         * @return JSON string
         */
        static std::string ExportInfrastructure(const Dto::Module::Module::ModuleList &modules, bool prettyPrint = false, bool includeObjects = false);

        /**
         * @brief Import the infrastructure
         *
         * @param jsonString infrastructure JSON string
         */
        static void ImportInfrastructure(const std::string &jsonString);

        /**
         * @brief Cleans the current infrastructure.
         *
         * <p>All SQS queues, SNS topics, S3 buckets etc. will be deleted, as well as all objects.</p>
         *
         * @param modules module list
         */
        static void CleanInfrastructure(const Dto::Module::Module::ModuleList &modules);

        /**
         * @brief Cleans the objects from the infrastructure.
         *
         * <p>Cleans all objects from the infrastructure. This means all SQS resources, SNS resources, S3 object keys, etc. will be deleted.</p>
         *
         * @param modules modules list
         */
        static void CleanObjects(const Dto::Module::Module::ModuleList &modules);

      private:

        /**
         * Module database
         */
        Database::PerformanceDatabase &_performanceDatabase;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_MODULE_SERVICE_H
