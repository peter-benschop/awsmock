//
// Created by vogje01 on 11/2/23.
//

#include <awsmock/core/MemoryMappedFile.h>

namespace AwsMock::Core {

  void MemoryMappedFile::OpenFile(const std::string &filename) {

    int fd = open(filename.c_str(), O_RDONLY);

    if (fd < 0) {
      log_error_stream(_logger) << "Could not open file for memory mapping" << std::endl;
      return;
    }

    long fileSize = FileUtils::FileSize(filename);

    _start = mmap(nullptr, fileSize, PROT_READ, MAP_SHARED, fd, 0);
    _membuffer = (char *) _start;

    if (_membuffer == MAP_FAILED) {
      log_error_stream(_logger) << "Could not memory map file: " << filename << std::endl;
      return;
    }
    close(fd);

    _mapped = true;
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