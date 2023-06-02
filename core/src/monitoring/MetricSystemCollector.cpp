//
// Created by vogje01 on 01/05/2023.
//

#include "awsmock/core/MetricSystemCollector.h"

namespace AwsMock::Core {

    MetricSystemCollector::MetricSystemCollector() : _logger(Poco::Logger::get("root")) {

        _virtualMemory = new Poco::Prometheus::Gauge(VIRTUAL_MEMORY);
        _realMemory = new Poco::Prometheus::Gauge(REAL_MEMORY);
        _totalThreads = new Poco::Prometheus::Gauge(TOTAL_THREADS);
        _totalCpu = new Poco::Prometheus::Gauge(TOTAL_CPU);
        _userCpu = new Poco::Prometheus::Gauge(USER_CPU);
        _systemCpu = new Poco::Prometheus::Gauge(SYSTEM_CPU);

        InitializeSystemCounter();
    }

    MetricSystemCollector::~MetricSystemCollector(){
        delete _virtualMemory;
        delete _realMemory;
        delete _totalThreads;
        delete _totalCpu;
        delete _userCpu;
        delete _systemCpu;
    }

    void MetricSystemCollector::InitializeSystemCounter() {

        FILE *file;
        struct tms timeSample{};
        char line[128];

        lastCPU = times(&timeSample);
        lastSysCPU = timeSample.tms_stime;
        lastUserCPU = timeSample.tms_utime;

        file = fopen("/proc/cpuinfo", "r");
        numProcessors = 0;
        while (fgets(line, 128, file) != nullptr) {
            if (strncmp(line, "processor", 9) == 0) numProcessors++;
        }
        fclose(file);
        numProcessors /= 2;
        poco_debug(_logger, "Got number of processors, numProcs: " + std::to_string(numProcessors));
    }

    void MetricSystemCollector::onTimer(Poco::Timer& timer) {
         CollectSystemCounter();
    }

    void MetricSystemCollector::CollectSystemCounter() {
        poco_trace(_logger, "System collector starting");

        std::string line;
        std::ifstream ifs("/proc/self/status");
        while (ifs) {
            std::getline(ifs, line);

            if (StringUtils::Contains(line, "VmSize:")) {
                double value = std::stod(StringUtils::Split(line, ':')[1]);
                _virtualMemory->set(value);
                poco_trace(_logger, "Virtual memory: " + std::to_string(value));
            }
            if (StringUtils::Contains(line, "VmRSS:")) {
                double value = std::stod(StringUtils::Split(line, ':')[1]);
                _realMemory->set(value);
                poco_trace(_logger, "Real Memory: " + std::to_string(value));
            }
            if (StringUtils::Contains(line, "Threads:")) {
                double value = std::stod(StringUtils::Split(line, ':')[1]);
                _totalThreads->set(value);
                poco_trace(_logger, "Total Threads: " + std::to_string(value));
            }
        }
        ifs.close();

        clock_t now;
        struct tms timeSample{};
        now = times(&timeSample);
        double totalPercent, userPercent, systemPercent;

        poco_trace(_logger,
                   "Now: " + std::to_string(now) + "/" + std::to_string(lastCPU) + "/" + std::to_string(lastSysCPU) +
                       "/" + std::to_string(lastUserCPU));
        if (now <= lastCPU || timeSample.tms_stime < lastSysCPU || timeSample.tms_utime < lastUserCPU) {
            // Overflow detection. Just skip this value.
            totalPercent = -1.0;
            poco_debug(_logger, "Invalid CPU values, skipping");
        } else {
            totalPercent = (double) ((timeSample.tms_stime - lastSysCPU) + (timeSample.tms_utime - lastUserCPU));
            totalPercent /= (double) (now - lastCPU);
            totalPercent /= numProcessors;
            totalPercent *= 100;
            _totalCpu->set(totalPercent);
            poco_trace(_logger, "Total CPU: " + std::to_string(totalPercent));

            userPercent = (double) (timeSample.tms_utime - lastUserCPU);
            userPercent /= (double) (now - lastCPU);
            userPercent /= numProcessors;
            userPercent *= 100;
            _userCpu->set(userPercent);
            poco_trace(_logger, "User CPU: " + std::to_string(userPercent));

            systemPercent = (double) (timeSample.tms_stime - lastSysCPU);
            systemPercent /= (double) (now - lastCPU);
            systemPercent /= numProcessors;
            systemPercent *= 100;
            _systemCpu->set(systemPercent);
            poco_trace(_logger, "System CPU: " + std::to_string(systemPercent));
        }
        lastCPU = now;
        lastSysCPU = timeSample.tms_stime;
        lastUserCPU = timeSample.tms_utime;
    }

} // namespace AwsMock::Core