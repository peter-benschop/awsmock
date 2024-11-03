//
// Created by vogje01 on 4/28/24.
//

#ifndef AWSMOCK_CORE_MONGO_UTILS_H
#define AWSMOCK_CORE_MONGO_UTILS_H

// Poco includes
#include <Poco/DateTime.h>

// Boost includes
#include <boost/date_time/posix_time/posix_time.hpp>

// Mongo included
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/pipeline.hpp>

namespace AwsMock::Database {

    using namespace boost::posix_time;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;
    using std::chrono::system_clock;

    class MongoUtils {

      public:

        /**
         * @brief Converts a Poco Datetime to a bsoncxx::date
         *
         * @param date Poco::DateTime value
         * @return bsoncxx::types::b_date
         */
        static bsoncxx::types::b_date ToBson(const Poco::DateTime &date);

        /**
         * @brief Converts a bsoncxx::date to a Poco Datetime
         *
         * @param date bsoncxx::types::b_date
         * @return Poco::DateTime value
         */
        static Poco::DateTime FromBson(bsoncxx::types::b_date date);
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_CORE_MONGO_UTILS_H
