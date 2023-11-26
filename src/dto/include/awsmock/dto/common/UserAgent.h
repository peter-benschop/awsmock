//
// Created by vogje01 on 11/26/23.
//

#ifndef AWSMOCK_DTO_COMMON_USERAGENT_H
#define AWSMOCK_DTO_COMMON_USERAGENT_H

// C++ includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/RegularExpression.h>
#include <Poco/Net/HTTPServerRequest.h>

// AwsMock includes
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/StringUtils.h>

namespace AwsMock::Dto::Common {

  struct UserAgent {

    /**
     * Client application
     */
     std::string clientApplication;

    /**
     * Client language
     */
    std::string clientLanguage;

    /**
     * Client OS
     */
    std::string clientOs;

    /**
     * Client executable type
     */
    std::string clientExecutableType;

    /**
     * Client prompt
     */
    bool clientPrompt;

    /**
     * Client request module
     */
    std::string clientModule;

    /**
     * Client command
     */
    std::string clientCommand;

    /**
     * Client content type
     */
    std::string contentType;

    /**
     * Getś the value from the user-agent string
     *
     * @param request HTTP server request
     * @return UserAgent DTO
     */
     void FromRequest(const Poco::Net::HTTPServerRequest &request);

    /**
     * Getś the value from the user-agent string
     *
     * @param request HTTP server request
     * @param service AWS service name
     * @return UserAgent DTO
     */
    void FromRequest(const Poco::Net::HTTPServerRequest &request, const std::string &service);

    /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] std::string ToString() const;

    /**
     * Stream provider.
     *
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const UserAgent &i);

  };

}
#endif //AWSMOCK_DTO_COMMON_USERAGENT_H
