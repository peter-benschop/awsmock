#pragma once

// C++ includes
#include <mutex>
#include <map>
#include <string>
#include <memory>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/ftpserver/FtpUser.h>

namespace AwsMock::FtpServer {

    class UserDatabase {

    public:
      /**
       * Constructor
       */
      UserDatabase() : _logger(Poco::Logger::get("FtpUser")) {}

      /**
       * Add a new user to the database.
       *
       * <p><cursive><bold>TODO:</bold> Should be replaced by Aws User database</cursive></p>
       *
       * @param username name of the user
       * @param password user password
       * @param local_root_path  local path
       * @param permissions permissions
       * @return
       */
      bool addUser(const std::string &username, const std::string &password, const std::string &local_root_path, Permission permissions);

      /**
       * Return a user by name
       *
       * @param username user name
       * @param password user password
       * @return FtpUser
       */
      std::shared_ptr<FtpUser> getUser(const std::string &username, const std::string &password) const;

    private:

      /**
       * Check whether the user is the anonymous user
       *
       * @param username name of the user
       * @return
       */
      bool isUsernameAnonymousUser(const std::string &username) const;

      /**
       * Server mutex
       */
      mutable std::mutex database_mutex_;

      /**
       * User database
       */
      std::map<std::string, std::shared_ptr<FtpUser>> database_;

      /**
       * Anonymous user
       */
      std::shared_ptr<FtpUser> anonymous_user_;

      /**
       * Logger
       */
      Core::LogStream _logger;
    };
}