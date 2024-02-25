//
// Created by vogje01 on 11/2/23.
//

#ifndef AWS_MOCK_CORE_MEMORY_MAPPED_FILE_H
#define AWS_MOCK_CORE_MEMORY_MAPPED_FILE_H

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

  /**
   * Memory mapped file utility.
   *
   * @author jens.vogt@opitz-consulting.com
   */
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

    /**
     * Returns true in case the file is mapped already.
     *
     * @return true, in case file is already mapped.
     */
    bool IsMapped() const { return _mapped; }

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

#endif // AWS_MOCK_CORE_MEMORY_MAPPED_FILE_H
