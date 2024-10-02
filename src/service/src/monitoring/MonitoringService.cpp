//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/monitoring/MonitoringService.h>

namespace AwsMock::Service {

    Dto::Monitoring::GetCountersResponse MonitoringService::GetCounters(const Dto::Monitoring::GetCountersRequest &request) {
        log_trace << "Get counters request, request: " << request.ToString();

        Dto::Monitoring::GetCountersResponse response;
        try {

            // Get counters from database
            response.counters = _database.GetRollingMean(request.name, request.start, request.end, 5);

            log_trace << "Monitoring create bucket count: " << response.counters.size();

            return response;

        } catch (Poco::Exception &exc) {
            log_error << "Monitoring get counters failed, message: " << exc.message();
            throw Core::ServiceException(exc.message());
        }
        return response;
    }

}// namespace AwsMock::Service
