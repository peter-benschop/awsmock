//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_S3_WORKER_H
#define AWSMOCK_SERVICE_S3_WORKER_H

// C++ includes
#include <filesystem>

// Boost includes
#include <boost/filesystem.hpp>

// AwsMock includes
#include <awsmock/repository/S3Database.h>

namespace AwsMock::Service {

    using namespace boost::filesystem;

    /**
     * @brief S3 worker thread
     *
     * Used as background thread to do maintenance work, like resetting resources, deleted S3 objects not existing in the database anymore.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class S3Worker {

      public:

        /**
         * @brief Constructor
         */
        explicit S3Worker() = default;

        /**
         * @brief Synchronize S3 object between filesystem and database.
         */
        [[maybe_unused]] void SyncObjects();

      private:

        /**
         * Database connection
         */
        Database::S3Database &_s3Database = Database::S3Database::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SQS_WORKER_H
