//
// Created by vogje01 on 12/11/2022.
//

#include <awsmock/core/SystemUtils.h>

namespace AwsMock::Core {

    ExecResult SystemUtils::Exec(const std::string &cmd) {
        // set up file redirection
        std::filesystem::path redirection = std::filesystem::absolute(".output.temp");
        std::string command = cmd + " > " + redirection.string() + " 2>&1";

        // execute command
        auto status = std::system(command.c_str());

        // read redirection file and remove the file
        std::ifstream output_file(redirection);
        std::string output((std::istreambuf_iterator<char>(output_file)), std::istreambuf_iterator<char>());
        std::filesystem::remove(redirection);

        return ExecResult{status, output};
    }

    std::string SystemUtils::GetCurrentWorkingDir() {
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        std::string path = {std::string(result, (count > 0) ? count : 0)};
        return path.substr(0, path.find_last_of('/'));
    }

    std::string SystemUtils::GetHomeDir() {
        std::string homeDir;
        if (getenv("HOME") != nullptr) {
            homeDir = std::string(getenv("HOME"));
        } else {
            homeDir = std::string(getpwuid(getuid())->pw_dir);
        }
        return homeDir;
    }

    std::string SystemUtils::SetHeader(const std::string &method, const std::string &url, const std::string &contentType, long contentLength) {
        return Poco::toUpper(method) + " " + url + " HTTP/1.1\nHost:localhost\nConnection:close\nContentType:" + contentType + "\nContent-Length:"
            + std::to_string(contentLength) + "\n\n";
    }

    std::string SystemUtils::SendFileViaDomainSocket(const std::string &socketPath, const std::string &header, const std::string &fileName) {

        int sock = 0;
        unsigned long data_len = 0;
        struct sockaddr_un remote{};
        char recv_msg[s_recv_len];

        if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
            poco_error(Poco::Logger::get("SystemUtils"), "Client: Error on socket() call");
            return "Client: Error on socket() call";
        }

        remote.sun_family = AF_UNIX;
        strcpy(remote.sun_path, socketPath.c_str());
        data_len = strlen(remote.sun_path) + sizeof(remote.sun_family);

        if (connect(sock, (struct sockaddr *) &remote, data_len) == -1) {
            poco_error(Poco::Logger::get("SystemUtils"), "Client: Error on connect call");
            return "Client: Error on connect call";
        }
        poco_debug(Poco::Logger::get("SystemUtils"), "Client: Connected to docker daemon");

        std::ifstream file(fileName, std::ios::binary);
        file.seekg(0, std::ios::end);
        long fileSize = file.tellg();
        file.close();

        char *fileBuffer = new char[fileSize];
        file.open(fileName, std::ios::binary);
        file.seekg(0, std::ios::beg);
        file.read(fileBuffer, fileSize);
        file.close();

        // Send header
        if (send(sock, header.c_str(), header.size(), 0) == -1) {
            poco_error(Poco::Logger::get("SystemUtils"), "Client: Error on send() call");
        }

        // Send body
        unsigned int bytesSent = 0;
        long bytesToSend = 0;

        while (bytesSent < fileSize) {
            if (fileSize - bytesSent >= CHUNK_SIZE)
                bytesToSend = CHUNK_SIZE;
            else
                bytesToSend = fileSize - bytesSent;
            send(sock, fileBuffer + bytesSent, bytesToSend, 0);
            bytesSent += bytesToSend;
        }

        // Get response
        std::string output;
        memset(recv_msg, 0, s_recv_len * sizeof(char));
        while (recv(sock, recv_msg, s_recv_len, 0) > 0) {
            output += std::string(recv_msg);
        }
        close(sock);
        return output;
    }
}