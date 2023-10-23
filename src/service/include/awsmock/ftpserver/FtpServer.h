#pragma once

// C++ includes
#include <memory>
#include <string>
#include <utility>

#define FTP_DEFAULT_PORT 21
#define FTP_DEFAULT_HOST "localhost"
#define FTP_DEFAULT_ADDRESS "0.0.0.0"
#define FTP_BASE_DIR "/tmp/awsmock/data/transfer"
#define FTP_BUCKET "transfer-server"

// C++ includes
#include <awsmock/core/Configuration.h>
#include <awsmock/ftpserver/Permissions.h>

namespace AwsMock::FtpServer {

  /** Private implementation */
  class FtpServerImpl;

  /**
   * @brief The fineftp::TransferFtpServer is a simple FTP server library.
   *
   * Using the TransferFtpServer class is simple:
   *   1. Create an instance
   *   2. Add a user
   *   3. Start the server
   *
   * Then your server is up and running. In code it will look like this:
   *
   * @code{.cpp}
   *
   *   fineftp::TransferFtpServer server(2121);
   *   server.addUserAnonymous("C:\\", fineftp::Permission::All);
   *   server.start();
   *
   * @endcode
   *
   */
  class FtpServer {

    public:
      /**
       * @brief Creates an FTP Server instance that will listen on the the given control port and accept connections from the given network interface.
       *
       * If no port is provided, the default FTP Port 21 is used. If you want to
       * use that port, make sure that your application runs as root.
       *
       * Instead of using a predefined port, the operating system can choose a
       * free port port. Use port=0, if that behaviour is desired. The chosen port
       * can be determined by with getPort().
       *
       * @param port: The port to start the FTP server on. Defaults to 21.
       * @param host: The host to accept incoming connections from.
       */
      // TransferFtpServer(const std::string &address, uint16_t port = 21);

      /**
       * @brief Creates an FTP Server instance that will listen on the the given control port.
       *
       * If no port is provided, the default FTP Port 21 is used. If you want to
       * use that port, make sure that your application runs as root.
       *
       * Instead of using a predefined port, the operating system can choose a
       * free port port. Use port=0, if that behaviour is desired. The chosen port
       * can be determined by with getPort().
       *
       * This constructor will create an FTP Server binding to IPv4 0.0.0.0 and
       * Thus accepting connections from any IPv4 address.
       * For security reasons it might be desirable to bind to a specific IP
       * address. Use TransferFtpServer(const std::string&, uint16_t) for that purpose.
       *
       * @param port: The port to start the FTP server on. Defaults to 21.
       */
      // TransferFtpServer(uint16_t port = 21);

      explicit FtpServer(const Core::Configuration &configuration, std::string serverName, int port, std::string address);

      // Destructor
      ~FtpServer();

      /**
       * @brief Adds a new user
       *
       * Adds a new user with a given username, password, local root path and
       * permissions.
       *
       * Note that the username "anonymous" and "ftp" are reserved, as those are
       * well-known usernames usually used for accessing FTP servers without a
       * password. If adding a user with any of those usernames, the password will
       * be ignored, any user will be able to log in with any password!
       *
       * The Permissions are flags that are or-ed bit-wise and control what the
       * user will be able to do.
       *
       * @param username:         The username for login
       * @param password:         The user's password
       * @param local_root_path:  A path to any resource on the local filesystem that will be accessed by the user
       * @param permissions:      A bit-mask of what the user will be able to do.
       *
       * @return True if adding the user was successful (i.e. it didn't exit already).
       */
      bool addUser(const std::string &username, const std::string &password, const std::string &local_root_path, Permission permissions);

      /**
       * @brief Adds the "anonymous" / "ftp" user that FTP clients use to access FTP servers without password
       *
       * @param local_root_path:  A path to any resource on the local filesystem that will be accessed by the user
       * @param permissions:      A bit-mask of what the user will be able to do.
       *
       * @return True if adding the anonymous user was successful (i.e. it didn't exit already).
       */
      bool addUserAnonymous(const std::string &local_root_path, Permission permissions);

      /**
       * @brief Starts the FTP Server
       *
       * @param thread_count: The size of the thread pool to use. Must not be 0.
       *
       * @return True if the Server has been started successfully.
       */
      bool start(size_t thread_count = 1);

      /**
       * @brief Stops the FTP Server
       *
       * All operations will be cancelled as fast as possible. The clients will
       * not be informed about the shutdown.
       */
      void stop();

      /**
       * @brief Sets the name of the server
       */
      void setName(const std::string &name) { _name = name; }

      /**
       * @brief Returns the name of the server
       */
      std::string getName() { return _name; }

      /**
       * @brief Returns the number of currently open connections
       *
       * @return the number of open connections
       */
      int getOpenConnectionCount() const;

      /**
       * @brief Get the control port that the FTP server is listening on
       *
       * When the server was created with a specific port (not 0), this port will
       * be returned.
       * If the server however was created with port 0, the operating system will
       * choose a free port. This method will return that port.
       *
       * @return The control port the server is listening on
       */
      [[nodiscard]] int getPort() const;

      /**
       * @brief Get the ip address that the FTP server is listening for.
       *
       * @return The ip address the FTP server is listening for.
       */
      [[nodiscard]] std::string getAddress() const;

    private:

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Actual implementation
       */
      std::unique_ptr<FtpServerImpl> _ftp_server;

      /**
       * Name of the server
       */
      std::string _serverName;

      /**
       * Hostname for the server
       */
      std::string _host;

      /**
       * IP address for the server
       */
      std::string _address;

      /**
       * Hostname for the server
       */
      int _port;

      /**
       * Name of the server
       */
      std::string _name;

      /**
       * Maximal number of threads
       */
      int _maxThreads;

      /**
       * Data directory
       */
      std::string _dataDir;
  };

}
