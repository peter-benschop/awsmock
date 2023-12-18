
#include <iostream>
#include <utility>
#include "awsmock/core/LogStream.h"

namespace AwsMock::Core {

  //
  // LogStreamBuf
  //
  LogStreamBuf::LogStreamBuf(Poco::Logger &logger, Poco::Message::Priority priority, std::size_t bufferCapacity) : _logger(logger), _priority(priority) {
    _message.reserve(bufferCapacity);
  }

  LogStreamBuf::~LogStreamBuf() = default;

  void LogStreamBuf::setPriority(Poco::Message::Priority priority) {
    _priority = priority;
  }

  void LogStreamBuf::setChannel(const Poco::Channel::Ptr &channel) {
    _logger.setChannel(channel);
  }

  void LogStreamBuf::setFile(const char *file) {
    _file = file;
  }

  void LogStreamBuf::setLine(int line) {
    _line = line;
  }

  void LogStreamBuf::reserve(std::size_t capacity) {
    _message.reserve(capacity);
  }

  int LogStreamBuf::writeToDevice(char c) {
    Poco::Mutex::ScopedLock lock(_mutex);
    if (c == '\n' || c == '\r') {
      if (!_message.empty()) {
        Poco::Message msg(_logger.name(), _message, _priority, _file, _line);
        _logger.log(msg);
        _message.clear();
      }
    } else
      _message += c;
    return c;
  }

  //
  // LogIOS
  //
  LogIOS::LogIOS(Poco::Logger &logger, Poco::Message::Priority priority, std::size_t bufferCapacity) : _buf(logger, priority, bufferCapacity) {
    init(&_buf);
  }

  LogIOS::~LogIOS() = default;

  LogStreamBuf *LogIOS::rdbuf() {
    return &_buf;
  }

  Poco::AutoPtr<Poco::ConsoleChannel> LogStream::_pConsoleChannel = new Poco::ConsoleChannel();
  Poco::AutoPtr<Poco::FileChannel> LogStream::_pFileChannel = new Poco::FileChannel();
  Poco::AutoPtr<Poco::PatternFormatter> LogStream::_pFormatter = new Poco::PatternFormatter(LOG_PATTERN);
  Poco::AutoPtr<Poco::FormattingChannel> LogStream::_pFormattingChannel = new Poco::FormattingChannel(_pFormatter, _pConsoleChannel);

  //
  // LogStream
  //
  LogStream::LogStream(Poco::Logger &logger, Poco::Message::Priority priority, std::size_t bufferCapacity) : LogIOS(logger, priority, bufferCapacity), std::ostream(&_buf) {
    logger.setChannel(_pFormattingChannel);
  }

  LogStream::~LogStream() = default;

  void LogStream::setChannel(const Poco::Channel::Ptr& channel) {
    _buf.setChannel(channel);
  }

  void LogStream::setConsoleChannel() {
    Poco::AutoPtr<Poco::ConsoleChannel> channel = new Poco::ConsoleChannel();
    Poco::AutoPtr<Poco::PatternFormatter> formatter(new Poco::PatternFormatter(LOG_PATTERN));
    Poco::Logger::root().setChannel(new Poco::FormattingChannel(formatter, channel));
  }

  void LogStream::setFileChannel(const std::string &filename) {
    Poco::Logger::root().getChannel()->close();
    _pFileChannel = new Poco::FileChannel(filename);
    _pFileChannel->setProperty("rotation", "10 M");
    _pFileChannel->setProperty("archive", "timestamp");
    _pFormattingChannel = new Poco::FormattingChannel(_pFormatter, _pFileChannel);
    Poco::Logger::root().setChannel(_pFormattingChannel);
  }

  LogStream &LogStream::fatal() {
    return priority(Poco::Message::PRIO_FATAL);
  }

  LogStream &LogStream::fatal(const char *file, int line) {
    _buf.setFile(file);
    _buf.setLine(line);
    return priority(Poco::Message::PRIO_FATAL);
  }

  LogStream &LogStream::fatal(const std::string &message) {
    _buf.logger().fatal(message);
    return priority(Poco::Message::PRIO_FATAL);
  }

  LogStream &LogStream::critical() {
    return priority(Poco::Message::PRIO_CRITICAL);
  }

  LogStream &LogStream::critical(const char *file, int line) {
    _buf.setFile(file);
    _buf.setLine(line);
    return priority(Poco::Message::PRIO_CRITICAL);
  }

  LogStream &LogStream::critical(const std::string &message) {
    _buf.logger().critical(message);
    return priority(Poco::Message::PRIO_CRITICAL);
  }

  LogStream &LogStream::error() {
    return priority(Poco::Message::PRIO_ERROR);
  }

  LogStream &LogStream::error(const char *file, int line) {
    _buf.setFile(file);
    _buf.setLine(line);
    return priority(Poco::Message::PRIO_ERROR);
  }

  LogStream &LogStream::error(const std::string &message) {
    _buf.logger().error(message);
    return priority(Poco::Message::PRIO_ERROR);
  }

  LogStream &LogStream::warning() {
    return priority(Poco::Message::PRIO_WARNING);
  }

  LogStream &LogStream::warning(const char *file, int line) {
    _buf.setFile(file);
    _buf.setLine(line);
    return priority(Poco::Message::PRIO_WARNING);
  }

  LogStream &LogStream::warning(const std::string &message) {
    _buf.logger().warning(message);
    return priority(Poco::Message::PRIO_WARNING);
  }

  LogStream &LogStream::notice() {
    return priority(Poco::Message::PRIO_NOTICE);
  }

  LogStream &LogStream::notice(const std::string &message) {
    _buf.logger().notice(message);
    return priority(Poco::Message::PRIO_NOTICE);
  }

  LogStream &LogStream::notice(const char *file, int line) {
    _buf.setFile(file);
    _buf.setLine(line);
    return priority(Poco::Message::PRIO_NOTICE);
  }

  LogStream &LogStream::information() {
    return priority(Poco::Message::PRIO_INFORMATION);
  }

  LogStream &LogStream::information(const char *file, int line) {
    _buf.setFile(file);
    _buf.setLine(line);
    return priority(Poco::Message::PRIO_INFORMATION);
  }

  LogStream &LogStream::information(const std::string &message) {
    _buf.logger().information(message);
    return priority(Poco::Message::PRIO_INFORMATION);
  }

  LogStream &LogStream::debug() {
    return priority(Poco::Message::PRIO_DEBUG);
  }

  LogStream &LogStream::debug(const char *file, int line) {
    _buf.setFile(file);
    _buf.setLine(line);
    return priority(Poco::Message::PRIO_DEBUG);
  }

  LogStream &LogStream::debug(const std::string &message) {
    _buf.logger().debug(message);
    return priority(Poco::Message::PRIO_DEBUG);
  }

  LogStream &LogStream::trace() {
    return priority(Poco::Message::PRIO_TRACE);
  }

  LogStream &LogStream::trace(const char *file, int line) {
    _buf.setFile(file);
    _buf.setLine(line);
    return priority(Poco::Message::PRIO_TRACE);
  }

  LogStream &LogStream::trace(const std::string &message) {
    _buf.logger().trace(message);
    return priority(Poco::Message::PRIO_TRACE);
  }

  LogStream &LogStream::priority(Poco::Message::Priority priority) {
    _buf.setPriority(priority);
    return *this;
  }

  LogStream &LogStream::level(const std::string &level) {
    _buf.logger().setLevel(level);
    return *this;
  }

  void LogStream::SetGlobalLevel(const std::string &level) {
    Poco::Logger::root().setLevel(level);

    std::vector<std::string> names;
    Poco::Logger::names(names);
    for (const auto &n : names) {
      Poco::Logger::get(n).setLevel(level);
    }

  }
} // namespace Poco
