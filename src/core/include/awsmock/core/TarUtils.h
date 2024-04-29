//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_CORE_TARUTILS_H
#define AWSMOCK_CORE_TARUTILS_H

// C++ standard includes
#include <fcntl.h>
#include <string>
#include <unistd.h>

// Poco includes
#include <Poco/RecursiveDirectoryIterator.h>
#include <Poco/String.h>

// Archive includes
#include <archive.h>
#include <archive_entry.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>

namespace AwsMock::Core {

    /**
     * TAR compresion utilities
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class TarUtils {

      public:

        /**
         * Constructor
         */
        TarUtils() = default;

        /**
           * Archive a whole directory tree to a tar file.
           *
           * @param tarFile name of the tar file
           * @param directory directory name
           */
        static void TarDirectory(const std::string &tarFile, const std::string &directory);

      private:

        /**
         * Writes archive single file to the Tar archive.
         *
         * @param archive tar archive.
         * @param fileName name of the file to write
         * @param removeDir remove name of the directory from filename
         * @param isDir directory flag
         * @param isLink link flag, needed to preserve links
         */
        static void WriteFile(struct archive *archive,
                              const std::string &fileName,
                              const std::string &removeDir,
                              bool isDir,
                              bool isLink);

        /**
         * Read a symbolic link.
         *
         * @param path path to link.
         * @return target path.
         */
        static std::string Readsymlink(const std::string &path);
    };

}// namespace AwsMock::Core

#endif//AWSMOCK_CORE_TARUTILS_H