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
        return Poco::toUpper(method) + " " + url + " HTTP/1.1\nHost:localhost\nConnection:close\nContent-Type:" + contentType + "\nContent-Length:"
            + std::to_string(contentLength) + "\n\n";
    }

    std::string SystemUtils::SendFileViaDomainSocket(const char *socketPath, const std::string &header, const std::string &fileName) {

        int sock = 0;
        unsigned long data_len = 0;
        struct sockaddr_un remote{};
        char recv_msg[s_recv_len];

        if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
            poco_error(Poco::Logger::get("SystemUtils"), "Client: Error on socket() call");
            return "Client: Error on socket() call";
        }

        remote.sun_family = AF_UNIX;
        strcpy(remote.sun_path, socketPath);
        data_len = strlen(remote.sun_path) + sizeof(remote.sun_family);

        if (connect(sock, (struct sockaddr *) &remote, data_len) == -1) {
            poco_error(Poco::Logger::get("SystemUtils"), "Client: Error on connect call");
            return "Client: Error on connect call";
        }
        poco_trace(Poco::Logger::get("SystemUtils"), "Client: Connected to docker daemon");

        std::ifstream file(fileName, std::ios::binary);
        file.seekg(0, std::ios::end);
        long fileSize = file.tellg();
        file.close();

        int filefd = open(fileName.c_str(), O_RDONLY);
        if (filefd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        /*char *fileBuffer = new char[fileSize];
        file.open(fileName, std::ios::binary);
        file.seekg(0, std::ios::beg);
        file.read(fileBuffer, fileSize);
        file.close();*/

        /* std::cout << "========================== Header ==========================" << std::endl;
         std::cout << header << std::endl;
         std::cout << "========================== Header ==========================" << std::endl;*/

        // Send header
        if (send(sock, header.c_str(), header.size(), 0) == -1) {
            poco_error(Poco::Logger::get("SystemUtils"), "Client: Error on send() call");
        }

        // Send body
        off_t offset = 0;
        ssize_t bytesSend = sendfile(sock, filefd, &offset, fileSize);

        /*unsigned int bytesSent = 0;
        long bytesToSend = 0;

        while (bytesSent < fileSize) {
            if (fileSize - bytesSent >= CHUNK_SIZE)
                bytesToSend = CHUNK_SIZE;
            else
                bytesToSend = fileSize - bytesSent;
            send(sock, fileBuffer + bytesSent, bytesToSend, 0);
            bytesSent += bytesToSend;
        }*/

        // Get response
        std::stringstream output;
        memset(recv_msg, 0, s_recv_len * sizeof(char));
        while (recv(sock, recv_msg, s_recv_len, 0) > 0) {
            output << recv_msg;
        }
        std::cout << "========================== Response ==========================" << std::endl;
        std::cout << std::to_string(bytesSend) << std::endl;
        std::cout << output.str() << std::endl;
        std::cout << "========================== Response ==========================" << std::endl;
        close(sock);
        return GetBody(output.str());
    }

    std::string SystemUtils::SendMessageViaDomainSocket(const char *socketPath, const std::string &header, const std::string &body) {

        int sock = 0;
        unsigned long data_len = 0;
        struct sockaddr_un remote{};
        char recv_msg[s_recv_len];

        if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
            poco_error(Poco::Logger::get("SystemUtils"), "Client: Error on socket() call");
            return "Client: Error on socket() call";
        }

        remote.sun_family = AF_UNIX;
        strcpy(remote.sun_path, socketPath);
        data_len = strlen(remote.sun_path) + sizeof(remote.sun_family);

        if (connect(sock, (struct sockaddr *) &remote, data_len) == -1) {
            poco_error(Poco::Logger::get("SystemUtils"), "Client: Error on connect call");
            return "Client: Error on connect call";
        }
        poco_trace(Poco::Logger::get("SystemUtils"), "Client: Connected to docker daemon");

        /*std::cout << "========================== Header ==========================" << std::endl;
        std::cout << header << std::endl;
        std::cout << "========================== Header ==========================" << std::endl;

        std::cout << "=========================== Body ===========================" << std::endl;
        std::cout << body << std::endl;
        std::cout << "=========================== Body ===========================" << std::endl;*/

        // Send message
        std::string message = header + body;
        if (send(sock, message.c_str(), message.size(), 0) == -1) {
            poco_error(Poco::Logger::get("SystemUtils"), "Client: Error on send() call");
        }

        // Get response
        std::stringstream output;
        memset(recv_msg, 0, s_recv_len * sizeof(char));
        while (recv(sock, recv_msg, s_recv_len, 0) > 0) {
            output << recv_msg;
        }
        close(sock);
        /*
        std::cout << "========================== Response ==========================" << std::endl;
        std::cout << output.str() << std::endl;
        std::cout << "========================== Response ==========================" << std::endl;
         */
        return GetBody(output.str());
    }

    std::string SystemUtils::GetBody(const std::string &output) {

        Poco::RegularExpression regex(R"(.*[\r?|\n?]{2}([0-9a-f]+)[\r?|\n?]{1}(.*)[\r?|\n?]{2}.*)");
        Poco::RegularExpression::MatchVec posVec;
        int matches = regex.match(output, 0, posVec);

        if (matches == 3) {
            return output.substr(posVec[2].offset + 1, posVec[2].length - 1);
        }
        return "Match not found";
    }
}