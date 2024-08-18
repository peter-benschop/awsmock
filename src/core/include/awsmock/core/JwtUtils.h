//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_CORE_JWT_UTILS_H
#define AWSMOCK_CORE_JWT_UTILS_H

// C++ standard includes
#include <fcntl.h>
#include <string>

// Poco includes
//#include <Poco/Crypto/RSAKey.h>
//#include <Poco/JWT/Signer.h>
//#include <Poco/JWT/Token.h>
//#include <Poco/String.h>

// JWT-cpp includes
#include <jwt-cpp/jwt.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>

namespace AwsMock::Core {

    /**
     * @brief JWT token utilities
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class JwtUtils {

      public:

        /**
         * @brief Constructor
         */
        JwtUtils() = default;

        /**
         * @brief Create a new JWT token
         *
         * @param privateKey RSA private key
         * @param issuer issuer of the token
         * @param payload payload
         * @return JWT token string
         */
        static std::string CreateToken(const std::string &privateKey, const std::string &subject, const std::map<std::string, std::string> &payload);

        /**
         * @brief Verifies a JWT token
         *
         * @param publicKey RSA public key
         * @param jwt token string
         * @param issuer issuer of the token
         * @return JWT token
         */
        static bool VerifyToken(const std::string &publicKey, const std::string &jwt, const std::string &issuer);
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_JWT_UTILS_H