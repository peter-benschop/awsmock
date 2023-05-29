//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/core/DirUtils.h"

namespace AwsMock::Core {

    std::string DirUtils::GetTempDir() {
        return Poco::replace(Poco::toLower(Poco::Path::temp() + Poco::UUIDGenerator().createRandom().toString()), "-", "");
    }

    std::string DirUtils::CreateTempDir() {
        Poco::File tempDir = Poco::File(GetTempDir());
        tempDir.createDirectories();
        return tempDir.path();
    }

    bool DirUtils::DirectoryExists(const std::string &dirName) {
        Poco::File tempDir = Poco::File(dirName);
        return tempDir.exists();
    }

    long DirUtils::DirectoryCountFiles(const std::string &dirName) {
        Poco::DirectoryIterator it(dirName);
        Poco::DirectoryIterator end;
        int count = 0;
        while (it != end) {
            count++;
            ++it;
        }
        return count;
    }

    bool DirUtils::DirectoryEmpty(const std::string &dirName) {
        return DirectoryCountFiles(dirName) == 0;
    }

    void DirUtils::MakeDirectory(const std::string &dirName, bool recursive) {
        Poco::File file(dirName);
        if (recursive) {
            file.createDirectories();
        } else {
            file.createDirectory();
        }
    }

    std::vector<std::string> DirUtils::ListFiles(const std::string &dirName) {
        Poco::DirectoryIterator it(dirName);
        Poco::DirectoryIterator end;
        std::vector<std::string> fileNames;
        while (it != end) {
            fileNames.push_back(it.name());
            ++it;
        }
        return fileNames;
    }

    std::vector<std::string> DirUtils::ListFiles(const std::string &dirName, const std::string &pattern) {
        Poco::RegularExpression re(pattern);
        Poco::DirectoryIterator it(dirName);
        Poco::DirectoryIterator end;
        std::vector<std::string> fileNames;
        while (it != end) {
            if (re.match(it.name())) {
                fileNames.push_back(it.name());
            }
            ++it;
        }
        return fileNames;
    }

    void DirUtils::DeleteDirectory(const std::string &dirName, bool recursive) {
        if (DirectoryExists(dirName)) {
            Poco::File tempDir = Poco::File(dirName);
            tempDir.remove(recursive);
        }
    }
}