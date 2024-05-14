//
// Created by vogje01 on 5/12/24.
//

#ifndef AWSMOCK_SERVICE_S3_HASH_CREATOR_H
#define AWSMOCK_SERVICE_S3_HASH_CREATOR_H

// Poco includes
#include <Poco/Path.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/Task.h>
#include <awsmock/entity/s3/Object.h>
#include <awsmock/repository/S3Database.h>

#define DEFAULT_DATA_DIR "/home/awsmock/data"

namespace AwsMock::Service {

    /**
     * Asynchronous hash creator (MD5, SHA1, SHA256)
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class S3HashCreator : public Core::Task {

      public:

        /**
         * Constructor
         *
         * @param _algorithms vector of algorithm names
         * @param object S3 object to hash
         */
        explicit S3HashCreator(const std::vector<std::string> &algorithms, Database::Entity::S3::Object &object) : Core::Task("s3-hash-creator"), _object(object), _algorithms(algorithms) {}

        /**
         * Work method
         */
        void Run() override;

      private:

        /**
         * Hash algorithm
         */
        std::vector<std::string> _algorithms;

        /**
         * S3 object
         */
        Database::Entity::S3::Object _object;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_S3_HASH_CREATOR_H
