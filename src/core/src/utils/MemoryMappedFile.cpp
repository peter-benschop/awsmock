//
// Created by vogje01 on 11/2/23.
//

#include <awsmock/core/MemoryMappedFile.h>

namespace AwsMock::Core {

    Poco::Mutex MemoryMappedFile::_mutex;

    bool MemoryMappedFile::OpenFile(const std::string &filename) {

        int fd = open(filename.c_str(), O_RDONLY);

        if (fd < 0) {
            log_error << "Could not open file for memory mapping";
            return false;
        }

        _fileSize = FileUtils::FileSize(filename);

        _start = mmap(nullptr, _fileSize, PROT_READ, MAP_SHARED, fd, 0);
        _membuffer = (char *) _start;

        if (_membuffer == MAP_FAILED) {
            close(fd);
            log_error << "Could not memory map file: " << filename;
            return false;
        }
        close(fd);

        _mapped = true;
        return _mapped;
    }

    void MemoryMappedFile::CloseFile() {
        if (munmap(_start, _fileSize) < 0) {
            log_error << "Could not unmap file";
        }
        _mapped = false;
    }

    long MemoryMappedFile::ReadChunk(long start, long length, char *buffer) {
        Poco::ScopedLock Lock(_mutex);
        if (length > _fileSize) {
            length = _fileSize;
        }
        memcpy(buffer, _membuffer + start, length);
        return length;
    }

} // namespace AwsMock::Core