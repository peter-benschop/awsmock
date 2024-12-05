//
// Created by vogje01 on 18/05/2023.
//

#include <awsmock/core/TarUtils.h>

namespace AwsMock::Core {

    void TarUtils::TarDirectory(const std::string &tarFile, const std::string &directory) {

        using namespace boost::filesystem;

        archive *a = archive_write_new();
        archive_write_add_filter_gzip(a);
        archive_write_set_format_gnutar(a);
        archive_write_open_filename(a, tarFile.c_str());

        recursive_directory_iterator dir(directory), end;
        int count = 0;
        while (dir != end) {
            if (dir->path() != tarFile) {
                WriteFile(a, dir->path().c_str(), directory, dir->is_directory(), dir->is_symlink());
                count++;
            }
            ++dir;
        }
        archive_write_close(a);
        archive_write_free(a);
    }

    void TarUtils::WriteFile(archive *archive, const std::string &fileName, const std::string &removeDir, const bool isDir, const bool isLink) {

        struct stat st {};
        char buff[8192];

        const std::string entryName = StringUtils::Replace(fileName.c_str(), removeDir.c_str(), "");
        log_trace << "Removed directory, name: " << entryName;

        stat(fileName.c_str(), &st);
        archive_entry *entry = archive_entry_new();// Note 2
        archive_entry_set_pathname(entry, entryName.c_str());
        archive_entry_set_size(entry, st.st_size);
        std::string link;
        if (isDir) {
            archive_entry_set_filetype(entry, S_IFDIR);
            archive_entry_set_perm(entry, 0755);
            archive_entry_set_uid(entry, 0);
            archive_entry_set_gid(entry, 0);
        } else if (isLink) {
            link = Readsymlink(fileName);
            archive_entry_set_filetype(entry, AE_IFLNK);
            archive_entry_set_symlink(entry, link.c_str());
            archive_entry_set_perm(entry, 0644);
            archive_entry_set_uid(entry, 0);
            archive_entry_set_gid(entry, 0);
        } else {
            archive_entry_set_filetype(entry, S_IFREG);
            archive_entry_set_perm(entry, 0644);
            archive_entry_set_uid(entry, 0);
            archive_entry_set_gid(entry, 0);
        }
        archive_write_header(archive, entry);
        const int fd = open(fileName.c_str(), O_RDONLY);
        long len = read(fd, buff, sizeof(buff));
        while (len > 0) {
            archive_write_data(archive, buff, len);
            len = read(fd, buff, sizeof(buff));
            log_trace << "File written to archive, name: " << entryName;
        }
        close(fd);
        archive_entry_free(entry);
    }

    std::string TarUtils::Readsymlink(const std::string &path) {
#ifndef _WIN32
        size_t len;
        if (char buf[1024]; (len = readlink(path.c_str(), buf, sizeof(buf) - 1)) != -1) {
            buf[len] = '\0';
            return {buf};
        }
#endif
        return "";
    }
}// namespace AwsMock::Core
