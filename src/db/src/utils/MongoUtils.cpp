//
// Created by vogje01 on 4/28/24.
//

#include <awsmock/utils/MongoUtils.h>

namespace AwsMock::Database {

    /*bsoncxx::types::b_date MongoUtils::ToBson(const ptime &dateTime) {

        ptime epoch(boost::gregorian::date(1970, 1, 1));
        bsoncxx::types::b_date bDate{std::chrono::milliseconds((dateTime - epoch).total_milliseconds())};
        return bDate;
    }

    ptime MongoUtils::FromBson(const bsoncxx::types::b_date &bDate) {

        ptime epoch(boost::gregorian::date(1970, 1, 1));
        ptime pt(epoch, bDate.value.count());
        return pt;
    }*/

    bsoncxx::types::b_date MongoUtils::ToBson(const Poco::DateTime &date) {

        if (date.timestamp().epochTime() != 0) {
            bsoncxx::types::b_date bDate{std::chrono::milliseconds(date.timestamp().epochMicroseconds() / 1000)};
            return bDate;
        }
        bsoncxx::types::b_date bDate{std::chrono::milliseconds(0)};
        return bDate;
    }

    Poco::DateTime MongoUtils::FromBson(bsoncxx::types::b_date bDate) {

        Poco::DateTime pDate;
        if (bDate.value.count() != 0) {
            pDate = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(bDate.value) / 1000));
            return pDate;
        }
        return pDate;
    }

}// namespace AwsMock::Database