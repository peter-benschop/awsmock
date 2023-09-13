#pragma once

#include "Permissions.h"
#include <string>

namespace AwsMock::FtpServer {

    struct FtpUser {
      FtpUser(const std::string &password, const std::string &local_root_path, const Permission permissions)
          : password_(password), local_root_path_(local_root_path), permissions_(permissions) {}

      const std::string password_;
      const std::string local_root_path_;
      const Permission permissions_;
    };
}