//
// Created by vogje01 on 12/12/24.
//

#ifndef AWSMOCK_CORE_ZIP_UTILS_H
#define AWSMOCK_CORE_ZIP_UTILS_H

// Standard C++ includes
#include <fstream>
#include <list>
#include <string>

// ZLib includes
#include <minizip/unzip.h>

// AwsMock includes
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/StringUtils.h>

namespace AwsMock::Core {

    class ZipUtils {

      public:

        /**
         * @brief Uncompress a ZIP file to a target directory
         *
         * @param zipFile full path of ZIP file
         * @param targetPath target directory
         */
        static void Uncompress(const std::string &zipFile, const std::string &targetPath);

      private:

        /**
         * @brief Get file content
         *
         * @param szZipArchive ZIP archive file
         * @param szFilename file name
         * @param contents file content
         */
        static bool ExtractZipFileContents(const char *szZipArchive, const char *szFilename, std::string &contents);

        static std::list<std::string> GetZipFilenames(const char *szZipArchive);
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_ZIP_UTILS_H
