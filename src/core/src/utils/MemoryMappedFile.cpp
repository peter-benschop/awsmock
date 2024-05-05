//
// Created by vogje01 on 11/2/23.
//

#include <awsmock/core/MemoryMappedFile.h>

namespace AwsMock::Core {

    bool MemoryMappedFile::OpenFile(const std::string &filename) {
#ifdef _WIN32
        CacheHint _hint = Normal;
        DWORD winHint = 0;
        switch (_hint) {
            case Normal:
                winHint = FILE_ATTRIBUTE_NORMAL;
                break;
            case SequentialScan:
                winHint = FILE_FLAG_SEQUENTIAL_SCAN;
                break;
            case RandomAccess:
                winHint = FILE_FLAG_RANDOM_ACCESS;
                break;
            default:
                break;
        }

        // open file
        _file = ::CreateFileA(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, winHint, NULL);
        if (!_file)
            return false;

        // file size
        LARGE_INTEGER result;
        if (!GetFileSizeEx(_file, &result))
            return false;
        _fileSize = static_cast<uint64_t>(result.QuadPart);

        // convert to mapped mode
        _mappedFile = ::CreateFileMapping(_file, NULL, PAGE_READONLY, 0, 0, NULL);
        _mapped = true;
#else
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
#endif
        return _mapped;
    }

    void MemoryMappedFile::CloseFile() {
#ifdef _WIN32
        if (_mappedFile) {
            ::CloseHandle(_mappedFile);
            _mappedFile = nullptr;
            log_debug << "Memory mapped file closed";
        }
#else
        if (munmap(_start, _fileSize) < 0) {
            log_error << "Could not unmap file";
        }
        log_debug << "Memory mapped file closed";
#endif
        _mapped = false;
    }

    long MemoryMappedFile::ReadChunk(long start, long length, char *buffer) {
        if (length > _fileSize) {
            length = _fileSize;
        }
        memcpy(buffer, _membuffer + start, length);
        return length;
    }

}// namespace AwsMock::Core