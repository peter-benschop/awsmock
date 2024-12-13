//
// Created by vogje01 on 01/05/2023.
//

#include "awsmock/service/monitoring/MetricSystemCollector.h"

namespace AwsMock::Monitoring {

    MetricSystemCollector::MetricSystemCollector() {
        tms timeSample{};

        _lastCPU = times(&timeSample);
        _lastSysCPU = timeSample.tms_stime;
        _lastUserCPU = timeSample.tms_utime;
        _numProcessors = Core::SystemUtils::GetNumberOfCores() / 2;
        log_debug << "Got number of processors, numProcs: " << _numProcessors;
    }

    void MetricSystemCollector::CollectSystemCounter() {
        log_trace << "System collector starting";

        std::string line;
        std::ifstream ifs("/proc/self/status");
        while (ifs) {
            std::getline(ifs, line);

            if (Core::StringUtils::Contains(line, "VmSize:")) {
                double value = std::stod(Core::StringUtils::Split(line, ':')[1]);
                MetricService::instance().SetGauge(VIRTUAL_MEMORY, value);
                log_trace << "Virtual memory: " << value;
            }
            if (Core::StringUtils::Contains(line, "VmRSS:")) {
                double value = std::stod(Core::StringUtils::Split(line, ':')[1]);
                MetricService::instance().SetGauge(REAL_MEMORY, value);
                log_trace << "Real Memory: " << value;
            }
            if (Core::StringUtils::Contains(line, "Threads:")) {
                double value = std::stod(Core::StringUtils::Split(line, ':')[1]);
                MetricService::instance().SetGauge(TOTAL_THREADS, value);
                log_trace << "Total Threads: " << value;
            }
        }
        ifs.close();

        clock_t now;
        tms timeSample{};
        now = times(&timeSample);

        log_trace << "Now: " << now << "/" << _lastCPU << "/" << _lastSysCPU << "/" << _lastUserCPU;
        if (now <= _lastCPU || timeSample.tms_stime < _lastSysCPU || timeSample.tms_utime < _lastUserCPU) {
            // Overflow detection. Just skip this value.
            log_debug << "Invalid CPU values, skipping";
        } else {
            double totalPercent;
            double systemPercent;
            double userPercent;
            totalPercent = static_cast<double>(timeSample.tms_stime - _lastSysCPU + (timeSample.tms_utime - _lastUserCPU));
            totalPercent /= static_cast<double>(now - _lastCPU);
            totalPercent /= _numProcessors;
            totalPercent *= 100;
            MetricService::instance().SetGauge(TOTAL_CPU, totalPercent);
            log_trace << "Total CPU: " << totalPercent;

            userPercent = static_cast<double>(timeSample.tms_utime - _lastUserCPU);
            userPercent /= static_cast<double>(now - _lastCPU);
            userPercent /= _numProcessors;
            userPercent *= 100;
            MetricService::instance().SetGauge(USER_CPU, userPercent);
            log_trace << "User CPU: " << userPercent;

            systemPercent = static_cast<double>(timeSample.tms_stime - _lastSysCPU);
            systemPercent /= static_cast<double>(now - _lastCPU);
            systemPercent /= _numProcessors;
            systemPercent *= 100;
            MetricService::instance().SetGauge(SYSTEM_CPU, systemPercent);
            log_trace << "System CPU: " << systemPercent;
        }
        _lastCPU = now;
        _lastSysCPU = timeSample.tms_stime;
        _lastUserCPU = timeSample.tms_utime;
        log_trace << "System collector finished";
    }

}// namespace AwsMock::Monitoring