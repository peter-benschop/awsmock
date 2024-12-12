// #include <zlib/unzip.h>

#include <awsmock/core/ZipUtils.h>

namespace AwsMock::Core {

    void ZipUtils::Uncompress(const std::string &zipFile, const std::string &targetPath) {

        for (const std::list<std::string> files = GetZipFilenames(zipFile.c_str()); const auto &file: files) {

            std::string content;
            ExtractZipFileContents(zipFile.c_str(), file.c_str(), content);
            if (StringUtils::EndsWith(file, "/")) {
                DirUtils::EnsureDirectory(targetPath + "/" + file);
            }
            std::ofstream out(targetPath + "/" + file, std::ios::binary);
            out << content;
            out.close();
        }
    }

    std::list<std::string> ZipUtils::GetZipFilenames(const char *szZipArchive) {
        std::list<std::string> results;
        if (const unzFile zip = unzOpen(szZipArchive)) {
            if (UNZ_OK == unzGoToFirstFile(zip)) {
                do {
                    if (char szFilename[BUFSIZ]; UNZ_OK == unzGetCurrentFileInfo(zip, nullptr, szFilename, sizeof(szFilename), nullptr, 0, nullptr, 0))
                        results.emplace_back(szFilename);
                } while (UNZ_OK == unzGoToNextFile(zip));
            }
        }
        return results;
    }

    /// extract the contents of szFilename inside szZipArchive
    bool ZipUtils::ExtractZipFileContents(const char *szZipArchive, const char *szFilename, std::string &contents) {
        bool result = false;
        if (const unzFile zip = unzOpen(szZipArchive)) {
            if (UNZ_OK == unzLocateFile(zip, szFilename, 0)) {
                if (UNZ_OK == unzOpenCurrentFile(zip)) {
                    char buffer[BUFSIZ];
                    size_t bytes;
                    while (0 < (bytes = unzReadCurrentFile(zip, buffer, sizeof(buffer)))) {
                        contents += std::string(buffer, bytes);
                    }
                    unzCloseCurrentFile(zip);
                    result = (bytes == 0);
                }
            }
            unzClose(zip);
        }
        return result;
    }

}// namespace AwsMock::Core