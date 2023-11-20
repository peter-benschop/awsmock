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

  MetricSystemCollector::~MetricSystemCollector() {
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
      if (strncmp(line, "processor", 9) == 0)
        numProcessors++;
    }
    fclose(file);
    numProcessors /= 2;
    log_debug_stream(_logger) << "Got number of processors, numProcs: " << numProcessors << std::endl;
  }

  void MetricSystemCollector::onTimer(Poco::Timer &timer) {
    CollectSystemCounter();
  }

  void MetricSystemCollector::CollectSystemCounter() {
    log_trace_stream(_logger) << "System collector starting" << std::endl;

    std::string line;
    std::ifstream ifs("/proc/self/state");
    while (ifs) {
      std::getline(ifs, line);

      if (StringUtils::Contains(line, "VmSize:")) {
        double value = std::stod(StringUtils::Split(line, ':')[1]);
        _virtualMemory->set(value);
        log_trace_stream(_logger) << "Virtual memory: " << value << std::endl;
      }
      if (StringUtils::Contains(line, "VmRSS:")) {
        double value = std::stod(StringUtils::Split(line, ':')[1]);
        _realMemory->set(value);
        log_trace_stream(_logger) << "Real Memory: " << value << std::endl;
      }
      if (StringUtils::Contains(line, "Threads:")) {
        double value = std::stod(StringUtils::Split(line, ':')[1]);
        _totalThreads->set(value);
        log_trace_stream(_logger) << "Total Threads: " << value << std::endl;
      }
    }
    ifs.close();

    clock_t now;
    struct tms timeSample{};
    now = times(&timeSample);
    double totalPercent, userPercent, systemPercent;

    log_trace_stream(_logger) << "Now: " << now << "/" << lastCPU << "/" << lastSysCPU << "/" << lastUserCPU << std::endl;
    if (now <= lastCPU || timeSample.tms_stime < lastSysCPU || timeSample.tms_utime < lastUserCPU) {
      // Overflow detection. Just skip this value.
      totalPercent = -1.0;
      log_debug_stream(_logger) << "Invalid CPU values, skipping" << std::endl;
    } else {
      totalPercent = (double) ((timeSample.tms_stime - lastSysCPU) + (timeSample.tms_utime - lastUserCPU));
      totalPercent /= (double) (now - lastCPU);
      totalPercent /= numProcessors;
      totalPercent *= 100;
      _totalCpu->set(totalPercent);
      log_trace_stream(_logger) << "Total CPU: " << totalPercent << std::endl;

      userPercent = (double) (timeSample.tms_utime - lastUserCPU);
      userPercent /= (double) (now - lastCPU);
      userPercent /= numProcessors;
      userPercent *= 100;
      _userCpu->set(userPercent);
      log_trace_stream(_logger) << "User CPU: " << userPercent << std::endl;

      systemPercent = (double) (timeSample.tms_stime - lastSysCPU);
      systemPercent /= (double) (now - lastCPU);
      systemPercent /= numProcessors;
      systemPercent *= 100;
      _systemCpu->set(systemPercent);
      log_trace_stream(_logger) << "System CPU: " << systemPercent << std::endl;
    }
    lastCPU = now;
    lastSysCPU = timeSample.tms_stime;
    lastUserCPU = timeSample.tms_utime;
  }

} // namespace AwsMock::Core