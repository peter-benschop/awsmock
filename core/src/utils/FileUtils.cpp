#include "awsmock/core/FileUtils.h"

namespace AwsMock::Core {

    std::string FileUtils::GetBasename(const std::string &fileName) {
        Poco::Path path(fileName);
        return path.getBaseName();
    }

    std::string FileUtils::GetExtension(const std::string &fileName) {
        Poco::Path path(fileName);
        return path.getExtension();
    }

    bool FileUtils::FileNameContainsString(const std::string &fileName, const std::string &pattern) {
        Poco::Path path(fileName);
        return path.getBaseName().find(pattern) != std::string::npos;
    }

    std::string FileUtils::GetTempFile(const std::string &extension) {
        return Poco::replace(Poco::toLower(Poco::Path::temp() + Poco::UUIDGenerator().createRandom().toString() + "." + extension), "-", "");
    }

    std::string FileUtils::GetTempFile(const std::string &dir, const std::string &extension) {
        return dir + Poco::Path::separator()
            + Poco::replace(Poco::toLower(Poco::Path::temp() + Poco::UUIDGenerator().createRandom().toString() + "." + extension), "-", "");
    }

    unsigned long FileUtils::FileSize(const std::string &fileName) {
        Poco::File file(fileName);
        return file.getSize();
    }

    void FileUtils::AppendBinaryFiles(const std::string &outFile, const std::string &inDir, const std::vector<std::string> &files) {
        std::ofstream ofs(outFile, std::ios::trunc | std::ios::out | std::ios::app | std::ios::binary);

        for(auto &it : files) {
            char ch;
            std::string inFile = inDir + Poco::Path::separator() + it;
            std::ifstream in(inFile, std::ios::in | std::ios::binary);
            while(in) {
                in.get(ch);
                if(in) {
                    ofs.put(ch);
                }
            }
        }
        ofs.close();
    }

    std::string FileUtils::CreateTempFile(const std::string &extension) {
        std::string tempFilename = GetTempFile(extension);
        std::ofstream tempFile;
        tempFile.open(tempFilename);
        tempFile << StringUtils::GenerateRandomString(100);
        tempFile.close();
        return tempFilename;
    }

    std::string FileUtils::CreateTempFile(const std::string &extension, int numBytes) {
        std::string tempFilename = GetTempFile(extension);
        std::ofstream tempFile;
        tempFile.open(tempFilename);
        tempFile << StringUtils::GenerateRandomString(numBytes);
        tempFile.close();
        return tempFilename;
    }

    std::string FileUtils::CreateTempFile(const std::string &dirName, const std::string &extension, int numBytes) {
        std::string tmpFileName = Poco::replace(Poco::UUIDGenerator().createRandom().toString(), "-", "") + "." + extension;
        std::ostringstream stringStream;
        stringStream << dirName << Poco::Path::separator() << tmpFileName;
        std::string tempFilename = stringStream.str();
        std::ofstream tempFile;
        tempFile.open(tempFilename);
        tempFile << StringUtils::GenerateRandomString(numBytes);
        tempFile.close();
        return tempFilename;
    }

    std::string FileUtils::CreateTempFile(const std::string &extension, const std::string &content) {
        std::string tempFilename = GetTempFile(extension);
        std::ofstream tempFile;
        tempFile.open(tempFilename);
        tempFile << content;
        tempFile.close();
        return tempFilename;
    }

    bool FileUtils::FileExists(const std::string &fileName) {
        Poco::File file(fileName);
        return file.exists();
    }

    std::string FileUtils::StripBasePath(const std::string &fileName) {
        return Poco::format("%s.%s", GetBasename(fileName), GetExtension(fileName));
    }

    void FileUtils::DeleteFile(const std::string &fileName) {
        Poco::File file(fileName);
        if (file.exists()) {
            file.remove();
        }
    }

    void FileUtils::unzipFiles(const std::string &zipFile, const std::string &dirName) {
        Poco::File tempDir = Poco::File(dirName);
        tempDir.createDirectories();
        poco_debug(Poco::Logger::get("FileUtils"), "Using output directory: " + dirName);

        std::ifstream inp(zipFile, std::ios::binary);
        poco_assert(inp);

        // Decompress to a temp dir
        Poco::Zip::Decompress dec(inp, dirName);

        // Decompress to directory
        dec.decompressAllFiles();
        poco_debug(Poco::Logger::get("FileUtils"), "File uncompressed, zipFile: " + zipFile + " directory:" + dirName);
    }

    void FileUtils::zipFiles(const std::string &zipFile, const std::string &dirName) {
        poco_debug(Poco::Logger::get("FileUtils"), "Using directory: " + dirName);

        std::ofstream out(zipFile, std::ios::binary);
        Poco::Zip::Compress com(out, true);
        com.addRecursive(Poco::Path(dirName));
        com.close();
        poco_debug(Poco::Logger::get("FileUtils"), "Files compressed, zipFile: " + zipFile + " directory:" + dirName);
    }
}