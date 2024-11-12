
//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/MonitoringDatabase.h>
#include <boost/date_time/posix_time/posix_time_duration.hpp>

namespace AwsMock::Database {

    typedef boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::mean>> Accumulator;

    MonitoringDatabase::MonitoringDatabase() : _databaseName(GetDatabaseName()), _monitoringCollectionName("monitoring") {}

    void MonitoringDatabase::IncCounter(const std::string &name, double value, const std::string &labelName, const std::string &labelValue) {
        log_trace << "Set counter value, name: " << name << " value: " << value << " labelName: " << labelName << " labelValue:" << labelValue;

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _monitoringCollection = (*client)[_databaseName][_monitoringCollectionName];
            auto session = client->start_session();

            try {

                bsoncxx::builder::basic::document searchDocument;
                searchDocument.append(kvp("name", name));

                if (!labelName.empty()) {
                    searchDocument.append(kvp("labelName", labelName));
                }
                if (!labelValue.empty()) {
                    searchDocument.append(kvp("labelValue", labelValue));
                }

                auto mResult = _monitoringCollection.find_one(searchDocument.extract());
                if (mResult) {
                    value += mResult.value()["value"].get_double().value;
                }

                session.start_transaction();

                bsoncxx::builder::basic::document document;
                document.append(kvp("name", name));
                if (!labelName.empty()) {
                    document.append(kvp("labelName", labelName));
                }
                if (!labelValue.empty()) {
                    document.append(kvp("labelValue", labelValue));
                }
                document.append(kvp("value", value));
                document.append(kvp("created", bsoncxx::types::b_date(Core::DateTimeUtils::LocalDateTimeNow())));

                auto insert_one_result = _monitoringCollection.insert_one(document.extract());
                session.commit_transaction();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        } else {
            log_info << "Performance counter not available if you running the memory DB";
        }
    }

    void MonitoringDatabase::SetGauge(const std::string &name, double value, const std::string &labelName, const std::string &labelValue) {
        log_trace << "Set gauge value, name: " << name << " value: " << value << " labelName: " << labelName << " labelValue:" << labelValue;

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _monitoringCollection = (*client)[_databaseName][_monitoringCollectionName];
            auto session = client->start_session();

            try {

                system_clock::time_point now = Core::DateTimeUtils::LocalDateTimeNow();
                system_clock::time_point end = Core::ceilTimePoint(now, std::chrono::seconds(300));
                system_clock::time_point middle = end - std::chrono::seconds(150);

                bsoncxx::builder::basic::document document;
                document.append(kvp("name", name));
                document.append(kvp("created", bsoncxx::types::b_date(middle)));
                if (!labelName.empty()) {
                    document.append(kvp("labelName", labelName));
                }
                if (!labelValue.empty()) {
                    document.append(kvp("labelValue", labelValue));
                }

                if (name.empty()) {
                    log_error << "Missing name";
                }
                session.start_transaction();
                auto mResult = _monitoringCollection.find_one(document.extract());
                if (mResult) {

                    double currentValue = mResult.value()["value"].get_double().value;
                    int currentCount = mResult.value()["count"].get_int32().value;
                    currentValue += value / static_cast<double>(++currentCount);
                    _monitoringCollection.update_one(make_document(kvp("_id", mResult.value()["_id"].get_oid())),
                                                     make_document(kvp("$set", make_document(kvp("value", currentValue), kvp("count", currentCount)))));

                } else {
                    if (name.empty()) {
                        log_error << "Missing name";
                    }
                    bsoncxx::builder::basic::document newDocument;
                    newDocument.append(kvp("value", value));
                    newDocument.append(kvp("count", 1));
                    newDocument.append(kvp("name", name));
                    newDocument.append(kvp("created", bsoncxx::types::b_date(middle)));
                    if (!labelName.empty()) {
                        newDocument.append(kvp("labelName", labelName));
                    }
                    if (!labelValue.empty()) {
                        newDocument.append(kvp("labelValue", labelValue));
                    }
                    _monitoringCollection.insert_one(newDocument.extract());
                }
                session.commit_transaction();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        } else {
            log_info << "Performance counter not available if you running the memory DB";
        }
    }

    std::vector<Database::Entity::Monitoring::Counter> MonitoringDatabase::GetRollingMean(const std::string &name, system_clock::time_point start, system_clock::time_point end, int step, const std::string &labelName, const std::string &labelValue) {
        log_trace << "Get rolling mean, name: " << name << " start: " << start << " end: " << end << " step: " << step << " labelName: " << labelName << " labelValue:" << labelValue;

        long offset = Core::DateTimeUtils::UtcOffset();

        std::vector<Database::Entity::Monitoring::Counter> result;
        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _monitoringCollection = (*client)[_databaseName][_monitoringCollectionName];

            try {

                mongocxx::options::find opts;
                opts.sort(make_document(kvp("created", 1)));

                bsoncxx::builder::basic::document document;
                document.append(kvp("name", name));
                document.append(kvp("created", make_document(kvp("$gte", bsoncxx::types::b_date(start)))), kvp("created", make_document(kvp("$lte", bsoncxx::types::b_date(end)))));
                if (!labelName.empty()) {
                    document.append(kvp("labelName", labelName));
                }
                if (!labelValue.empty()) {
                    document.append(kvp("labelValue", labelValue));
                }

                // Find and accumulate
                auto cursor = _monitoringCollection.find(document.extract(), opts);
                for (auto it: cursor) {
                    system_clock::time_point t = bsoncxx::types::b_date(it["created"].get_date().value);
                    Database::Entity::Monitoring::Counter counter = {.name = name, .performanceValue = it["value"].get_double().value, .timestamp = bsoncxx::types::b_date(it["created"].get_date().value - std::chrono::seconds(offset))};
                    result.emplace_back(counter);
                }
                log_debug << "Counters, name: " << name << " count: " << result.size();
                return result;
            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        } else {
            log_info << "Performance counter not available if you running the memory DB";
        }
        return {};
    }

    long MonitoringDatabase::DeleteOldMonitoringData(int retentionPeriod) {
        log_trace << "Deleting old monitoring data, retention:: " << retentionPeriod;

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _monitoringCollection = (*client)[_databaseName][_monitoringCollectionName];
            auto session = client->start_session();

            try {
                // Find and delete counters
                session.start_transaction();
                auto retention = system_clock::now() - std::chrono::hours(retentionPeriod * 24);
                auto mResult = _monitoringCollection.delete_many(make_document(kvp("created", make_document(kvp("$lte", bsoncxx::types::b_date(retention))))));
                log_debug << "Counters deleted, count: " << mResult.value().deleted_count();
                session.commit_transaction();
                return mResult.value().deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        } else {
            log_info << "Performance counter not available if you running the memory DB";
        }
        return 0;
    }
}// namespace AwsMock::Database
