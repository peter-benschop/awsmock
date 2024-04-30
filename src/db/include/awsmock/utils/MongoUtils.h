//
// Created by vogje01 on 4/28/24.
//

#ifndef AWSMOCK_CORE_MONGO_UTILS_H
#define AWSMOCK_CORE_MONGO_UTILS_H

// Poco includes
#include <Poco/DateTime.h>

// Mongo included
#include <bsoncxx/types.hpp>

namespace AwsMock::Database {

    class MongoUtils {

      public:

        /**
         * Converts a Poco Datetime to a bsoncxx::date
         *
         * @param date Poco::DateTime value
         * @return bsoncxx::types::b_date
         */
        static bsoncxx::types::b_date ToBson(const Poco::DateTime &date);

        /**
         * Converts a bsoncxx::date to a Poco Datetime
         *
         * @param date bsoncxx::types::b_date
         * @return Poco::DateTime value
         */
        static Poco::DateTime FromBson(bsoncxx::types::b_date);
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_CORE_MONGO_UTILS_H
