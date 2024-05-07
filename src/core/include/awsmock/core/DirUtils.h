//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWS_MOCK_CORE_DIRECTORY_UTILS_H
#define AWS_MOCK_CORE_DIRECTORY_UTILS_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/DirectoryIterator.h>
#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/RecursiveDirectoryIterator.h>
#include <Poco/RegularExpression.h>
#include <Poco/String.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/StringUtils.h>

namespace AwsMock::Core {

    struct SubstringCompare {

        char _delimiter;

        explicit SubstringCompare(char delimiter) : _delimiter(delimiter) {}

        bool operator()(std::string const &a, std::string const &b) const {

            std::string sa = Core::StringUtils::Split(a, _delimiter)[1];
            std::string sb = Core::StringUtils::Split(b, _delimiter)[1];

            return std::stol(sa) < std::stol(sb);
        }
    };

    /**
     * Directory utilities.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class DirUtils {

      public:

        /**
         * Returns a thread safe temp directory name.
         *
         * @return thread safe temp directory name
         */
        static std::string GetTempDir();

        /**
         * Returns relative path for the given directory.
         *
         * @param dir directory name
         * @return relative path to dir
         */
        static std::string RelativePath(const std::string &dir);

        /**
         * Creates an empty temporary directory
         *
         * @return name of the directory
         */
        static std::string CreateTempDir();

        /**
         * Creates an empty temporary directory within the given parent directory
         *
         * @param parent parent directory for the temporary directory
         * @return thread safe temp directory name
         */
        static std::string CreateTempDir(const std::string &parent);

        /**
         * Checks the existence of a directory
         *
         * @param dirName name of the directory.
         * @return true, if directory exists otherwise false.
         */
        static bool DirectoryExists(const std::string &dirName);

        /**
         * Count the number of files in the geven directory.
         *
         * @param dirName name of the directory.
         * @return toal number of files.
         */
        static long DirectoryCountFiles(const std::string &dirName);

        /**
         * Checks whether the directory is empty.
         *
         * @param dirName name of the directory.
         * @return true, if directory is empty.
         */
        static bool DirectoryEmpty(const std::string &dirName);

        /**
         * Creates an directory tree recursively
         *
         * @param dirName name of the directory.
         * @param recursive if true, create also all parent directories.
         */
        static void MakeDirectory(const std::string &dirName, bool recursive = true);

        /**
         * Ensures that a directory exists.
         *
         * <p>If it does not exist, it will be created.</p>
         *
         * @param dirName name of the directory.
         */
        static void EnsureDirectory(const std::string &dirName);

        /**
         * Checks whether the given file name is a directory.
         *
         * @param dirName name of the directory.
         * @return true if the supplied file name is actually a directory.
         */
        static bool IsDirectory(const std::string &dirName);

        /**
         * Get list of files
         *
         * @param dirName name of the directory
         * @param recursive recursively list files
         * @return vector of file names
         */
        static std::vector<std::string> ListFiles(const std::string &dirName, bool recursive = true);

        /**
         * Get a sorted list of files with the given prefix.
         *
         * @param dirName name of the directory
         * @param prefix regular expression which must match the filename
         * @return vector of file names
         */
        static std::vector<std::string> ListFilesByPrefix(const std::string &dirName, const std::string &prefix);

        /**
         * Get a list of files with the given pattern.
         *
         * @param dirName name of the directory
         * @param pattern regular expression which must match the filename
         * @param recursive recursively list files
         * @return vector of file names
         */
        static std::vector<std::string> ListFilesByPattern(const std::string &dirName, const std::string &pattern, bool recursive = true);

        /**
         * Deletes an whole directory tree.
         *
         * @param dirName directory name.
         * @param recursive if true deletes also all files in all directories recursively.
         */
        static void DeleteDirectory(const std::string &dirName, bool recursive = true);

        /**
         * Deletes all files in the directory, but not the directory itself.
         *
         * @param dirName directory name.
         */
        static void DeleteFilesInDirectory(const std::string &dirName);
    };

}// namespace AwsMock::Core

#endif// AWS_MOCK_CORE_DIRECTORY_UTILS_H
