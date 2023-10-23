//
// Created by root on 10/11/23.
//

#ifndef AWSMOCK_DTO_LAMBDA_INVOCATIONNOTIFICATION_H
#define AWSMOCK_DTO_LAMBDA_INVOCATIONNOTIFICATION_H

// C++ includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/Notification.h>

namespace AwsMock::Dto::Lambda {

  struct InvocationNotification : public Poco::Notification {

    /**
     * Function name
     */
    std::string functionName;

    /**
     * Payload
     */
    std::string payload;

    /**
     * AWS region
     */
    std::string region;

    /**
     * AWS user
     */
    std::string user;

    /**
     * Host name
     */
    std::string hostName;

    /**
     * Host name
     */
    int port;

    /**
     * Constructor
     *
     * @param functionName name of the lambda function
     * @param payload event payload
     * @param region AWS region
     * @param user AWS user
     * @param hostname hostname of the lambda function
     * @param port lambda function port
     */
    InvocationNotification(const std::string &functionName, const std::string &payload, const std::string &region, const std::string &user, const std::string &hostName, int port);

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
    friend std::ostream &operator<<(std::ostream &os, const InvocationNotification &i);
  };
}
#endif // AWSMOCK_DTO_LAMBDA_INVOCATIONNOTIFICATION_H
