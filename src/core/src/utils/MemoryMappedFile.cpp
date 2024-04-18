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
      log_error << "Could not open file for memory mapping, filename: " << filename << " errno: " << errno;
      return false;
    }

    long fileSize = FileUtils::FileSize(filename);

    _start = mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, _fd, 0);
    _membuffer = (char *) _start;

    if (_membuffer == MAP_FAILED) {
      log_error << "Memory map file failed, filename: " << filename << " errno: " << errno;
      return false;
    }

    _mapped = true;
    log_info << "Memory map file opened, filename: " << filename;

    return _mapped;
  }

  void MemoryMappedFile::CloseFile() {
    Poco::Mutex::ScopedLock lock(_mutex);
    /*if (munmap(_start, MEMORY_SIZE) < 0) {
      log_error << "Could not unmap file, filename: " << _filename;
    }*/
    close(_fd);
    log_debug << "Memory mapped file closed, filename: " << _filename;
    _mapped = false;
  }

  void MemoryMappedFile::ReadChunk(long start, long length, char *buffer) {
    Poco::ScopedLock Lock(_mutex);
    read(_fd, buffer, length);
    //memcpy(buffer, _membuffer + start, length);
  }

} // namespace AwsMock::Core