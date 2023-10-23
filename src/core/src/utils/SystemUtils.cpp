//
// Created by vogje01 on 12/11/2022.
//

#include <awsmock/core/SystemUtils.h>

namespace AwsMock::Core {

    Core::LogStream SystemUtils::_logger = Core::LogStream(Poco::Logger::get("SystemUtils"));

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
}