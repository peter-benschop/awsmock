#pragma once

// C++ includes
#include <vector>
#include <string>
#include <thread>
#include <atomic>

// Asio includes
#include <asio.hpp>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/ftpserver/FtpSession.h>
#include <awsmock/ftpserver/FtpUser.h>
#include <awsmock/ftpserver/UserDatabase.h>

namespace AwsMock::FtpServer {

    class FtpServerImpl {
    public:
      FtpServerImpl(const std::string &serverName, std::string address, uint16_t port, const Core::Configuration &configuration);

      // Copy (disabled)
      FtpServerImpl(const FtpServerImpl &) = delete;
      FtpServerImpl &operator=(const FtpServerImpl &) = delete;

      // Move (disabled, as we are storing the this pointer in lambda captures)
      FtpServerImpl &operator=(FtpServerImpl &&) = delete;
      FtpServerImpl(FtpServerImpl &&) = delete;

      ~FtpServerImpl();

      bool addUser(const std::string &username, const std::string &password, const std::string &local_root_path, Permission permissions);
      bool addUserAnonymous(const std::string &local_root_path, Permission permissions);

      bool start(size_t thread_count = 1);

      void stop();

      int getOpenConnectionCount();

      uint16_t getPort();

      std::string getAddress();

    private:
      void acceptFtpSession(const std::shared_ptr<FtpSession> &ftp_session, asio::error_code const &error);

    private:
      UserDatabase ftp_users_;

      const uint16_t port_;
      const std::string address_;

      std::vector<std::thread> thread_pool_;
      asio::io_service io_service_;
      asio::ip::tcp::acceptor acceptor_;

      std::atomic<int> open_connection_count_;

      /**
       * Name of the server
       */
      std::string _serverName;

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Logger
       */
      const Core::Configuration &_configuration;
    };
}
