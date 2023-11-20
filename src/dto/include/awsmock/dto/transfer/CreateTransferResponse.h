//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_TRANSFER_CREATETRANSFERRESPONSE_H
#define AWSMOCK_DTO_TRANSFER_CREATETRANSFERRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/dto/lambda/CreateFunctionResponse.h>

namespace AwsMock::Dto::Transfer {

  struct CreateTransferResponse {

    /**
     * Region
     */
    std::string region;

    /**
     * Server ID
     */
    std::string serverId;

    /**
     * ARN of the transfer
     */
    std::string arn;

    /**
     * Creates a JSON string from the object.
     *
     * @return JSON string
     */
    std::string ToJson() {

      try {
        Poco::JSON::Object rootJson;
        rootJson.set("Region", region);
        rootJson.set("ServerId", serverId);
        rootJson.set("Arn", arn);

        std::ostringstream os;
        rootJson.stringify(os);
        return os.str();

      } catch (Poco::Exception &exc) {
        throw Core::ServiceException(exc.message(), 500);
      }
    }

    /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] std::string ToString() const {
      std::stringstream ss;
      ss << (*this);
      return ss.str();
    }

    /**
     * Stream provider.
     *
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const CreateTransferResponse &r) {
      os << "CreateTransferResponse={region='" << r.region << "' serverId='" << r.serverId << "' arn='" << r.arn;
      return os;
    }
  };

} // namespace AwsMock::Dto::Transfer

#endif // AWSMOCK_DTO_TRANSFER_CREATETRANSFERRESPONSE_H
