
//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/MonitoringDatabase.h>

namespace AwsMock::Database {

    MonitoringDatabase::MonitoringDatabase() : _databaseName(GetDatabaseName()), _monitoringCollectionName("monitoring") {}

    void MonitoringDatabase::IncCounter(const std::string &name, double value, const std::string &labelName, const std::string &labelValue) {

        if (name.empty()) {
            log_warning << "empty name";
        }

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _monitoringCollection = (*client)[_databaseName][_monitoringCollectionName];
            auto session = client->start_session();

            try {

                bsoncxx::builder::basic::document document;
                document.append(kvp("name", name));

                if (!labelName.empty()) {
                    document.append(kvp("labelName", labelName));
                }
                if (!labelValue.empty()) {
                    document.append(kvp("labelValue", labelValue));
                }

                session.start_transaction();
                auto mResult = _monitoringCollection.find_one(document.extract());
                if (mResult) {
                    value += mResult.value()["value"].get_double().value;
                }
                document.append(kvp("value", value));
                document.append(kvp("created", bsoncxx::types::b_date(Core::DateTimeUtils::LocalDateTimeNow())));

                auto insert_one_result = _monitoringCollection.insert_one(document.extract());
                log_trace << "Counter incremented, oid: " << insert_one_result->inserted_id().get_string().value;
                session.commit_transaction();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        }
    }

    void MonitoringDatabase::SetGauge(const std::string &name, double value, const std::string &labelName, const std::string &labelValue) {

        if (name.empty()) {
            log_warning << "empty name";
        }
        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _monitoringCollection = (*client)[_databaseName][_monitoringCollectionName];
            auto session = client->start_session();

            try {

                system_clock::time_point now = Core::DateTimeUtils::LocalDateTimeNow();

                bsoncxx::builder::basic::document document;
                document.append(kvp("name", name));
                document.append(kvp("value", value));
                document.append(kvp("created", bsoncxx::types::b_date(Core::DateTimeUtils::LocalDateTimeNow())));
                if (!labelName.empty()) {
                    document.append(kvp("labelName", labelName));
                }
                if (!labelValue.empty()) {
                    document.append(kvp("labelValue", labelValue));
                }

                session.start_transaction();
                auto insert_one_result = _monitoringCollection.insert_one(document.extract());
                session.commit_transaction();
                //log_debug << "Gauge set, oid: " << insert_one_result->inserted_id().get_string().value;

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        }
    }

    std::vector<Database::Entity::Monitoring::Counter> MonitoringDatabase::GetRollingMean(const std::string &name, system_clock::time_point start, system_clock::time_point end, int step, const std::string &labelName, const std::string &labelValue) {

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
                boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::rolling_mean>> acc(boost::accumulators::tag::rolling_window::window_size = step);
                auto cursor = _monitoringCollection.find(document.extract(), opts);
                for (auto it: cursor) {
                    acc(it["value"].get_double().value);
                    Database::Entity::Monitoring::Counter counter = {.name = name, .performanceValue = boost::accumulators::rolling_mean(acc), .timestamp = bsoncxx::types::b_date(it["created"].get_date().value)};
                    result.emplace_back(counter);
                }
                acc.drop<boost::accumulators::tag::rolling_mean>();

                log_debug << "Counters, name: " << name << " count: " << result.size();
                return result;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        }
        return {};
    }
}// namespace AwsMock::Database
