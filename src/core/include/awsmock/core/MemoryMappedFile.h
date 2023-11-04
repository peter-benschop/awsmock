//
// Created by vogje01 on 11/2/23.
//

#ifndef AWSMOCK_CORE_MEMORYMAPPEDFILE_H
#define AWSMOCK_CORE_MEMORYMAPPEDFILE_H

// C includes
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

// C++ includes
#include <string>
#include <mutex>

// Poco includes
#include <Poco/SingletonHolder.h>

// AwsMock includes
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/LogStream.h>

#define MEMORY_SIZE (10 * 1024 * 1024) // 10GB

namespace AwsMock::Core {

  class MemoryMappedFile {

  public:

    /**
     * Constructor
     */
    MemoryMappedFile() : _logger(Poco::Logger::get("MemoryMappedFile")), _start(nullptr), _membuffer(nullptr), _mapped(false) {}

    /**
     * Singleton
     *
     * @return singleton instance
     */
    static MemoryMappedFile &instance() {
      static Poco::SingletonHolder<MemoryMappedFile> memoryMappedFile;
      return *memoryMappedFile.get();
    }

    /**
     * Opens a file and prepares the memory map
     *
     * @param filename name of the file.
     */
    void OpenFile(const std::string &filename);

    /**
     * Release all resources
     */
    void CloseFile();

    /**
     * Copy a chunk of data from the memory mapped file the provided output buffer
     *
     * @param start start index
     * @param end end index
     * @param buffer char buffer
     */
    void ReadChunk(long start, long end, char *buffer);

    bool IsMapped() { return _mapped; }
  private:

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Start pointer
     */
    void *_start;

    /**
     * Char buffer
     */
    char *_membuffer;

    /**
     * Mapped flag
     */
    bool _mapped;

    Poco::Mutex _mutex;
  };

} // namespace AwsMock::Core

#endif // AWSMOCK_CORE_MEMORYMAPPEDFILE_H
