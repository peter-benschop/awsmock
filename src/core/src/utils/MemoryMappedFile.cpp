//
// Created by vogje01 on 11/2/23.
//

#include <awsmock/core/MemoryMappedFile.h>

namespace AwsMock::Core {

  bool MemoryMappedFile::OpenFile(const std::string &filename) {

    _mapped = false;
    int fd = open(filename.c_str(), O_RDWR|O_CREAT, 0644);
    if (fd < 0) {
      log_error_stream(_logger) << "Could not open file for memory mapping, filename: " << filename << " errno: " << errno << std::endl;
      return false;
    }

    long fileSize = FileUtils::FileSize(filename);

    _start = mmap(nullptr, fileSize, PROT_READ, MAP_SHARED, fd, 0);
    _membuffer = (char *) _start;

    if (_membuffer == MAP_FAILED) {
      log_error_stream(_logger) << "Memory map file failed, filename: " << filename << " errno: " << errno<< std::endl;
      return false;
    }
    close(fd);

    _mapped = true;
    log_info_stream(_logger) << "Memory map file opened, filename: " << filename << std::endl;

    return _mapped;
  }

  void MemoryMappedFile::CloseFile() {
    if (munmap(_start, MEMORY_SIZE) < 0) {
      log_error_stream(_logger) << "Could not unmap file" << std::endl;
    }
    _mapped = false;
  }

  void MemoryMappedFile::ReadChunk(long start, long length, char *buffer) {
    Poco::ScopedLock Lock(_mutex);
    memcpy(buffer, _membuffer + start, length);
  }

} // namespace AwsMock::Core