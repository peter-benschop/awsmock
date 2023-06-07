//
// Created by vogje01 on 18/05/2023.
//

#include <awsmock/core/TarUtils.h>

namespace AwsMock::Core {

    void TarUtils::TarDirectory(const std::string &tarFile, const std::string &directory) {

        struct archive *a;
        a = archive_write_new();
        archive_write_add_filter_gzip(a);
        archive_write_set_format_pax_restricted(a); // Note 1
        archive_write_open_filename(a, tarFile.c_str());

        Poco::RecursiveDirectoryIterator it((std::string(directory)));
        Poco::RecursiveDirectoryIterator end;
        int count = 0;
        while (it != end) {
            if (it.path().toString() != tarFile) {
                WriteFile(a, it->path(), directory, it->isDirectory());
                count++;
            }
            ++it;
        }
        archive_write_close(a);
        archive_write_free(a);
    }

    void TarUtils::WriteFile(struct archive *archive, const std::string &fileName, const std::string &removeDir, bool isDir) {

        struct stat st{};
        struct archive_entry *entry;
        char buff[8192];
        long len;
        int fd;

        std::string entryName = Poco::replace(fileName, removeDir.c_str(), "");
        poco_trace(Poco::Logger::get("SystemUtils"), "Removed directory, name: " + entryName);

        stat(fileName.c_str(), &st);
        entry = archive_entry_new(); // Note 2
        archive_entry_set_pathname(entry, entryName.c_str());
        archive_entry_set_size(entry, st.st_size);
        if (isDir) {
            archive_entry_set_filetype(entry, AE_IFDIR);
        } else {
            archive_entry_set_filetype(entry, AE_IFREG);
        }
        archive_entry_set_perm(entry, 0644);
        archive_write_header(archive, entry);
        fd = open(fileName.c_str(), O_RDONLY);
        len = read(fd, buff, sizeof(buff));
        while (len > 0) {
            archive_write_data(archive, buff, len);
            len = read(fd, buff, sizeof(buff));
            poco_trace(Poco::Logger::get("TarUtils"), "File written to archive, name: " + entryName);
        }
        close(fd);
        archive_entry_free(entry);
    };
}
