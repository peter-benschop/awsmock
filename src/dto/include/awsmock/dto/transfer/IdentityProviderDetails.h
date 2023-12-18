//
// Created by vogje01 on 12/18/23.
//

#ifndef AWSMOCK_DTO_TRANSFER_IDENTITY_PROVIDER_DETAILS_H
#define AWSMOCK_DTO_TRANSFER_IDENTITY_PROVIDER_DETAILS_H

// C** includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::Transfer {

  /**
   *
   * Example JSON:
   * <pre>
   *   "IdentityProviderDetails": {
   *     "DirectoryId": "string",
   *     "Function": "string",
   *     "InvocationRole": "string",
   *     "SftpAuthenticationMethods": "string",
   *     "Url": "string"
   *  },
   */
  struct IdentityProviderDetails {

    /**
     * Directory ID
     */
    std::string directoryId;

    /**
     * Lambda function
     */
    std::string function;

    /**
     * Invocation role
     */
    std::string invocationRole;

    /**
     * SFTP authentication method
     */
    std::string sftpAuthenticationMethods;

    /**
     * Authentication URL
     */
    std::string url;

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
    friend std::ostream &operator<<(std::ostream &os, const IdentityProviderDetails &r);

  };

} // namespace AwsMock::Dto::Transfer

#endif // AWSMOCK_DTO_TRANSFER_IDENTITY_PROVIDER_DETAILS_H
