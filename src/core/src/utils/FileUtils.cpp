#include <execution>
#include "awsmock/core/FileUtils.h"
#include "awsmock/core/ResourceNotFoundException.h"

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

    std::string FileUtils::GetParentPath(const std::string &fileName) {
        std::filesystem::path path(fileName);
        return path.parent_path();
    }

    long FileUtils::FileSize(const std::string &fileName) {
        if (FileExists(fileName)) {
            return (long) std::filesystem::file_size({fileName.c_str()});
        }
        return -1;
    }

    void FileUtils::MoveTo(const std::string &sourceFileName, const std::string &targetFileName, bool createDir) {
        Poco::File sourceFile(sourceFileName);
        Poco::File targetFile(targetFileName);
        std::string parentPath = GetParentPath(targetFileName);
        if (createDir && !Core::DirUtils::DirectoryExists(parentPath)) {
            Poco::File parentFile(parentPath);
            parentFile.createDirectories();
        }
        sourceFile.renameTo(targetFileName);
    }

    void FileUtils::CopyTo(const std::string &sourceFileName, const std::string &targetFileName, bool createDir) {
        Poco::File sourceFile(sourceFileName);
        Poco::File targetFile(targetFileName);
        std::string parentPath = GetParentPath(targetFileName);
        if (createDir) {
            DirUtils::EnsureDirectory(parentPath);
        }
        sourceFile.copyTo(targetFileName);
    }

    void FileUtils::AppendBinaryFiles(const std::string &outFile, const std::string &inDir, const std::vector<std::string> &files) {
        std::ofstream ofs(outFile, std::ios::out | std::ios::trunc | std::ios::binary | std::ios::app);
        for (auto &it: files) {
            std::string inFile = inDir;
            inFile.append(Poco::Path::separator() + it);
            std::ifstream ifs(inFile, std::ios::in);
            long copied = Poco::StreamCopier::copyStream(ifs, ofs);
            if (copied != Core::FileUtils::FileSize(inFile)) {
                throw Poco::Exception("Invalid input file");
            }
            ofs.flush();
            ifs.close();
        }
        ofs.close();
    }

    // TODO: Calculate correct checksum: https://docs.aws.amazon.com/AmazonS3/latest/userguide/checking-object-integrity.html
    long FileUtils::AppendTextFiles(const std::string &outFile, const std::string &inDir, const std::vector<std::string> &files) {

        long copied = 0;
        std::ofstream ofs(outFile, std::ios::out | std::ios::trunc);
        for (auto &it: files) {
            std::string inFile = inDir;
            inFile.append(Poco::Path::separator() + it);
            std::ifstream ifs(inFile, std::ios::in);
            copied += Poco::StreamCopier::copyStream(ifs, ofs);
            ofs.flush();
            ifs.close();
        }
        ofs.close();
        return copied;
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

    std::string FileUtils::GetOwner(const std::string &fileName) {
        struct stat info{};
        stat(fileName.c_str(), &info);  // Error check omitted
        struct passwd *pw = getpwuid(info.st_uid);
        if (pw) {
            return pw->pw_name;
        }
        return {};
    }

    void FileUtils::DeleteFile(const std::string &fileName) {
        if (fileName.empty()) {
            return;
        }
        Poco::File file(fileName);
        if (file.exists()) {
            file.remove();
        }
    }

    void FileUtils::UnzipFiles(const std::string &zipFile, const std::string &dirName) {
        Poco::File tempDir = Poco::File(dirName);
        tempDir.createDirectories();

        std::ifstream inp(zipFile, std::ios::binary);
        poco_assert(inp);

        // Decompress to a temp dir
        Poco::Zip::Decompress dec(inp, dirName);

        // Decompress to directory
        dec.decompressAllFiles();
    }

    void FileUtils::ZipFiles(const std::string &zipFile, const std::string &dirName) {

        std::ofstream out(zipFile, std::ios::binary);
        Poco::Zip::Compress com(out, true);
        com.addRecursive(Poco::Path(dirName));
        com.close();
    }

    bool FileUtils::Touch(const std::string &fileName) {

        int fd = open(fileName.c_str(), O_WRONLY | O_CREAT | O_NOCTTY | O_NONBLOCK, 0666);
        if (fd < 0) {
            log_error << "Could not open file: " << fileName;
            return false;
        }
        int rc = utimensat(AT_FDCWD, fileName.c_str(), nullptr, 0);
        if (rc) {
            log_error << "Could not utimensat file: " << fileName;
            return false;
        }
        close(fd);
        return true;
    }

    void FileUtils::StripChunkSignature(const std::string &path) {
        std::string line;
        std::ifstream fin;
        std::string tempFile = GetTempFile("bin");

        fin.open(path);

        // Contents of path must be copied to a temp file then renamed back to the path file
        std::ofstream temp;
        temp.open(tempFile);

        // Write all lines to temp other than the line marked for erasing
        while (getline(fin, line)) {
            if (!StringUtils::ContainsIgnoreCase(line, "chunk-signature"))
                temp << line;
        }

        temp.close();
        fin.close();

        // Required conversion for remove and rename functions
        CopyTo(tempFile, path);
        DeleteFile(tempFile);
    }
}