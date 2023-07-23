//
// Created by vogje01 on 12/11/2022.
//

#include <awsmock/core/SystemUtils.h>
#include "awsmock/core/FileUtils.h"

namespace AwsMock::Core {

    Core::LogStream SystemUtils::_logger = Poco::Logger::get("SystemUtils");

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

    std::string SystemUtils::SetHeader(const std::string &method, const std::string &url, const std::string &contentType, unsigned long contentLength) {
        return Poco::toUpper(method) + " " + url + " HTTP/1.1\nHost:localhost\nConnection:close\nContent-Type:" + contentType + "\nContent-Length:"
            + std::to_string(contentLength) + "\n\n";
    }

    std::string SystemUtils::SendFileViaDomainSocket(const char *socketPath, const std::string &header, const std::string &fileName) {

        int sock = 0;
        unsigned long data_len = 0;
        struct sockaddr_un remote{};
        char recv_msg[s_recv_len];

        if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
            log_debug_stream(_logger) << "Client: Error on socket() call" << std::endl;
            return "Client: Error on socket() call";
        }

        remote.sun_family = AF_UNIX;
        strcpy(remote.sun_path, socketPath);
        data_len = strlen(remote.sun_path) + sizeof(remote.sun_family);

        if (connect(sock, (struct sockaddr *) &remote, data_len) == -1) {
            log_debug_stream(_logger) << "Client: Error on connect call" << std::endl;
            return "Client: Error on connect call";
        }
        poco_trace(Poco::Logger::get("SystemUtils"), "Client: Connected to docker daemon");

        long fileSize = FileUtils::FileSize(fileName);

        int filefd = open(fileName.c_str(), O_RDONLY);
        if (filefd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        log_trace_stream(_logger) << "Header: " << header << std::endl;

        // Send header
        if (send(sock, header.c_str(), header.size(), 0) == -1) {
            log_error_stream(_logger) << "Client: Error on send() call" << std::endl;
        }

        // Send body
        off_t offset = 0;
        ssize_t bytesSend = sendfile(sock, filefd, &offset, fileSize);
        log_debug_stream(_logger) << "File send, size: " << bytesSend << std::endl;

        // Get response
        std::stringstream output;
        memset(recv_msg, 0, s_recv_len * sizeof(char));
        while (recv(sock, recv_msg, s_recv_len, 0) > 0) {
            output << recv_msg;
        }
        log_trace_stream(_logger) << "Response: " << output.str() << std::endl;

        // Cleanup
        close(sock);

        return GetBody(output.str());
    }

    std::string SystemUtils::SendMessageViaDomainSocket(const char *socketPath, const std::string &header, const std::string &body) {

        int sock = 0;
        unsigned long data_len = 0;
        struct sockaddr_un remote{};
        char recv_msg[s_recv_len];

        if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
            log_error_stream(_logger) << "Client: Error on socket() call" << std::endl;
            return "Client: Error on socket() call";
        }

        remote.sun_family = AF_UNIX;
        strcpy(remote.sun_path, socketPath);
        data_len = strlen(remote.sun_path) + sizeof(remote.sun_family);

        if (connect(sock, (struct sockaddr *) &remote, data_len) == -1) {
            log_debug_stream(_logger) << "Client: Error on connect call" << std::endl;
            return "Client: Error on connect call";
        }
        log_trace_stream(_logger) << "Client: Connected to docker daemon" << std::endl;

        log_trace_stream(_logger) << "Header: " << header << std::endl;
        log_trace_stream(_logger) << "Body: " << body << std::endl;

        // Send message
        std::string message = header + body;
        if (send(sock, message.c_str(), message.size(), 0) == -1) {
            log_error_stream(_logger) << "Client: Error on send() call" << std::endl;
        }

        // Get response
        std::stringstream output;
        memset(recv_msg, 0, s_recv_len * sizeof(char));
        while (recv(sock, recv_msg, s_recv_len, 0) > 0) {
            output << recv_msg;
        }
        close(sock);
        log_trace_stream(_logger) << "Response: " << output.str() << std::endl;

        std::string temp = GetBody(output.str());
        return GetBody(output.str());
    }

    std::string SystemUtils::GetBody(const std::string &output) {

        // Remove unwanted characters
        std::stringstream sin, sout;
        sin << output;
        Core::StreamFilter::XmlCharacterStreamFilter(sin, sout);
        std::string body = sout.str();

        Poco::RegularExpression regex(R"(.*[\r?|\n?]+([0-9a-f]+)[\r?|\n?]{1}(.*)[\r?|\n?]{2}.*)");
        Poco::RegularExpression::MatchVec posVec;
        int matches = regex.match(body, 0, posVec);

        if (matches == 3) {
            return body.substr(posVec[2].offset + 1, posVec[2].length - 1);
        }
        return "Match not found";
    }
}