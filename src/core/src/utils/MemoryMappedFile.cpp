//
// Created by vogje01 on 11/2/23.
//

#include <awsmock/core/MemoryMappedFile.h>

namespace AwsMock::Core {

  bool MemoryMappedFile::OpenFile(const std::string &filename) {
    Poco::Mutex::ScopedLock lock(_mutex);

    _mapped = false;
    _filename=filename;

    _fd = open(filename.c_str(), O_RDWR | O_CREAT, 0644);
    if (_fd < 0) {
      log_error_stream(_logger) << "Could not open file for memory mapping, filename: " << filename << " errno: " << errno << std::endl;
      return false;
    }

    long fileSize = FileUtils::FileSize(filename);

    _start = mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, _fd, 0);
    _membuffer = (char *) _start;

    if (_membuffer == MAP_FAILED) {
      log_error_stream(_logger) << "Memory map file failed, filename: " << filename << " errno: " << errno << std::endl;
      return false;
    }

    _mapped = true;
    log_info_stream(_logger) << "Memory map file opened, filename: " << filename << std::endl;

    return _mapped;
  }

  void MemoryMappedFile::CloseFile() {
    Poco::Mutex::ScopedLock lock(_mutex);
    /*if (munmap(_start, MEMORY_SIZE) < 0) {
      log_error_stream(_logger) << "Could not unmap file, filename: " << _filename << std::endl;
    }*/
    close(_fd);
    log_debug_stream(_logger) << "Memory mapped file closed, filename: " << _filename << std::endl;
    _mapped = false;
  }

  void MemoryMappedFile::ReadChunk(long start, long length, char *buffer) {
    Poco::ScopedLock Lock(_mutex);
    read(_fd, buffer, length);
    //memcpy(buffer, _membuffer + start, length);
  }

} // namespace AwsMock::Core