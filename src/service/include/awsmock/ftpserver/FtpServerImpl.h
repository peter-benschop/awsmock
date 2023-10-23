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

      /**
       * Constructor
       *
       * @param serverName name of the server
       * @param address listen address
       * @param port listen port
       * @param configuration AwsMock configuration
       */
      FtpServerImpl(std::string serverName, std::string address, uint16_t port, const Core::Configuration &configuration);

      /**
       *  Copy (constrcutor disabled)
       */
      FtpServerImpl(const FtpServerImpl &) = delete;

      /**
       *  Copy (constrcutor disabled)
       */
      FtpServerImpl &operator=(const FtpServerImpl &) = delete;

      /**
       * Assigment constructor (disabled, as we are storing the this pointer in lambda captures)
       *
       * @return FTP server implementation
       */
      FtpServerImpl &operator=(FtpServerImpl &&) = delete;

      /**
       * Assigment constructor (disabled, as we are storing the this pointer in lambda captures)
       *
       * @return FTP server implementation
       */
      FtpServerImpl(FtpServerImpl &&) = delete;

      /**
       * Destructor
       */
      ~FtpServerImpl();

      /**
       * Add normal user.
       *
       * @param username name of the user
       * @param password user password
       * @param local_root_path home directory
       * @param permissions permissions
       * @return true if successful
       */
      bool addUser(const std::string &username, const std::string &password, const std::string &local_root_path, Permission permissions);

      /**
       * Add normal user.
       *
       * @param local_root_path home directory
       * @param permissions permissions
       * @return true if successful
       */
      bool addUserAnonymous(const std::string &local_root_path, Permission permissions);

      /**
       * Start the server
       *
       * @param thread_count thread count
       * @return true if successful
       */
      bool start(size_t thread_count = 1);

      /**
       * Stop the server
       */
      void stop();

      /**
       * Return the number of open connections
       *
       * @return number of open connections
       */
      int getOpenConnectionCount();

      /**
       * Return the listen port
       *
       * @return listening port
       */
      uint16_t getPort();

      /**
       * Return the listen address
       *
       * @return listening address
       */
      std::string getAddress();

    private:

      /**
       * Accept FTP session
       *
       * @param ftp_session FTP session
       * @param error error handler
       */
      void acceptFtpSession(const std::shared_ptr<FtpSession> &ftp_session, asio::error_code const &error);

      /**
       * User database
       */
      UserDatabase _ftpUsers;

      /**
       * FTP port
       */
      const uint16_t _port;

      /**
       * Socket listen address
       */
      const std::string _address;

      /**
       * FTP session thread pool
       */
      std::vector<std::thread> _threadPool;

      /**
       * Asio IO service
       */
      asio::io_service _ioService;

      /**
       * Asio session acceptor
       */
      asio::ip::tcp::acceptor _acceptor;

      /**
       * Nuber of open connections
       */
      std::atomic<int> _openConnectionCount;

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
