//
// Created by vogje01 on 01/05/2023.
//

#include <awsmock/core/MetricSystemCollector.h>

namespace AwsMock::Core {

    MetricSystemCollector::MetricSystemCollector() : Core::Timer("SystemCollector", 5) {

        _virtualMemory = new Poco::Prometheus::Gauge(VIRTUAL_MEMORY);
        _realMemory = new Poco::Prometheus::Gauge(REAL_MEMORY);
        _totalThreads = new Poco::Prometheus::Gauge(TOTAL_THREADS);
        _totalCpu = new Poco::Prometheus::Gauge(TOTAL_CPU);
        _userCpu = new Poco::Prometheus::Gauge(USER_CPU);
        _systemCpu = new Poco::Prometheus::Gauge(SYSTEM_CPU);
    }

    MetricSystemCollector::~MetricSystemCollector() {
        delete _virtualMemory;
        delete _realMemory;
        delete _totalThreads;
        delete _totalCpu;
        delete _userCpu;
        delete _systemCpu;
    }

    void MetricSystemCollector::Initialize() {
#ifndef _WIN32
        FILE *file;
        struct tms timeSample {};
        char line[128];

        lastCPU = times(&timeSample);
        lastSysCPU = timeSample.tms_stime;
        lastUserCPU = timeSample.tms_utime;

        file = fopen("/proc/cpuinfo", "r");
        numProcessors = 0;
        while (fgets(line, 128, file) != nullptr) {
            if (strncmp(line, "processor", 9) == 0)
                numProcessors++;
        }
        fclose(file);
        numProcessors /= 2;
        log_debug << "Got number of processors, numProcs: " << numProcessors;
#endif
    }

    void MetricSystemCollector::Run() {
        CollectSystemCounter();
    }

    void MetricSystemCollector::Shutdown() {
    }

    void MetricSystemCollector::CollectSystemCounter() {
        log_trace << "System collector starting";

#ifndef _WIN32
        std::string line;
        std::ifstream ifs("/proc/self/status");
        while (ifs) {
            std::getline(ifs, line);

            if (StringUtils::Contains(line, "VmSize:")) {
                double value = std::stod(StringUtils::Split(line, ':')[1]);
                _virtualMemory->set(value);
                log_trace << "Virtual memory: " << value;
            }
            if (StringUtils::Contains(line, "VmRSS:")) {
                double value = std::stod(StringUtils::Split(line, ':')[1]);
                _realMemory->set(value);
                log_trace << "Real Memory: " << value;
            }
            if (StringUtils::Contains(line, "Threads:")) {
                double value = std::stod(StringUtils::Split(line, ':')[1]);
                _totalThreads->set(value);
                log_trace << "Total Threads: " << value;
            }
        }
        ifs.close();

        clock_t now;
        struct tms timeSample {};
        now = times(&timeSample);
        double totalPercent, userPercent, systemPercent;

        log_trace << "Now: " << now << "/" << lastCPU << "/" << lastSysCPU << "/" << lastUserCPU;
        if (now <= lastCPU || timeSample.tms_stime < lastSysCPU || timeSample.tms_utime < lastUserCPU) {
            // Overflow detection. Just skip this value.
            totalPercent = -1.0;
            log_debug << "Invalid CPU values, skipping";
        } else {
            totalPercent = (double) ((timeSample.tms_stime - lastSysCPU) + (timeSample.tms_utime - lastUserCPU));
            totalPercent /= (double) (now - lastCPU);
            totalPercent /= numProcessors;
            totalPercent *= 100;
            _totalCpu->set(totalPercent);
            log_trace << "Total CPU: " << totalPercent;

            userPercent = (double) (timeSample.tms_utime - lastUserCPU);
            userPercent /= (double) (now - lastCPU);
            userPercent /= numProcessors;
            userPercent *= 100;
            _userCpu->set(userPercent);
            log_trace << "User CPU: " << userPercent;

            systemPercent = (double) (timeSample.tms_stime - lastSysCPU);
            systemPercent /= (double) (now - lastCPU);
            systemPercent /= numProcessors;
            systemPercent *= 100;
            _systemCpu->set(systemPercent);
            log_trace << "System CPU: " << systemPercent;
        }
        lastCPU = now;
        lastSysCPU = timeSample.tms_stime;
        lastUserCPU = timeSample.tms_utime;
#endif
    }

}// namespace AwsMock::Core