//
// Created by vogje01 on 10/2/24.
//

#ifndef AWSMOCK_REPOSITORY_PERFORMANCE_DATABASE_H
#define AWSMOCK_REPOSITORY_PERFORMANCE_DATABASE_H


// C++ standard includes
#include <string>

// Poco includes
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/exception/DatabaseException.h>
#include <awsmock/entity/monitoring/Counter.h>
#include <awsmock/repository/Database.h>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>
#include <boost/accumulators/statistics/stats.hpp>
namespace AwsMock::Database {


    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using std::chrono::system_clock;

    /**
     * @brief Performance MongoDB database.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class MonitoringDatabase : public DatabaseBase {

      public:

        /**
         * @brief Constructor
         */
        explicit MonitoringDatabase();

        /**
         * @brief Singleton instance
         */
        static MonitoringDatabase &instance() {
            static MonitoringDatabase s3Database;
            return s3Database;
        }

        /**
         * @brief Increments a metric counter
         *
         * @param name metric counter name
         * @param labelName metric label name
         * @param labelValue metric label name
         * @param value metric value
         */
        void IncCounter(const std::string &name, double value, const std::string &labelName = {}, const std::string &labelValue = {});

        /**
         * @brief Sets a metric gauge
         *
         * @param name metric counter name
         * @param labelName metric label name
         * @param labelValue metric label name
         * @param value metric value
         */
        void SetGauge(const std::string &name, double value, const std::string &labelName = {}, const std::string &labelValue = {});

        /**
         * @brief returns the rolling mean
         *
         * @param name counter name
         * @param start start timestamp
         * @param end stop timestamp
         * @param step steps
         * @param labelName label name
         * @param labelValue labelValue
         * @return list of counter values
         */
        std::vector<Database::Entity::Monitoring::Counter> GetRollingMean(const std::string &name, system_clock::time_point start, system_clock::time_point end, int step, const std::string &labelName = {}, const std::string &labelValue = {});

      private:

        /**
         * Database name
         */
        std::string _databaseName;

        /**
         * Performance collection name
         */
        std::string _performanceCollectionName;
    };

}// namespace AwsMock::Database

#endif//AWSMOCK_REPOSITORY_PERFORMANCE_DATABASE_H
