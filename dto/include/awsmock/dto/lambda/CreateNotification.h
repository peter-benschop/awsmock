//
// Created by root on 10/11/23.
//

#ifndef AWSMOCK_DTO_LAMBDA_CREATENOTIFICATION_H
#define AWSMOCK_DTO_LAMBDA_CREATENOTIFICATION_H

// C++ includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/Notification.h>

namespace AwsMock::Dto::Lambda {

  struct CreateNotification : public Poco::Notification {

    /**
     * Zip file content
     */
    std::string zipFileContent;

    /**
     * Lambda function OID
     */
    std::string functionId;

    /**
     * Constructor
     *
     * @param zipFileContent content of the zip file as string
     * @param functionId lambda function OID
     */
    CreateNotification(const std::string &zipFileContent, const std::string &functionId);

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
    friend std::ostream &operator<<(std::ostream &os, const CreateNotification &i);
  };
}
#endif // AWSMOCK_DTO_LAMBDA_CREATENOTIFICATION_H
