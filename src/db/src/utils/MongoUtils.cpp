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

    void MongoUtils::SetDatetime(bsoncxx::builder::basic::document &document, const std::string &attribute, system_clock::time_point datetime) {
        if (datetime.time_since_epoch().count() > 0) {
            document.append(kvp(attribute, bsoncxx::types::b_date(datetime)));
        } else {
            document.append(kvp(attribute, bsoncxx::types::b_null()));
        }
    }

    system_clock::time_point MongoUtils::GetDatetime(const mongocxx::stdx::optional<bsoncxx::document::view> &document, const std::string &attribute) {
        if (document.value()[attribute].type() != bsoncxx::type::k_null) {
            return bsoncxx::types::b_date(document.value()[attribute].get_date());
        }
        return system_clock::time_point::min();
    }

}// namespace AwsMock::Database