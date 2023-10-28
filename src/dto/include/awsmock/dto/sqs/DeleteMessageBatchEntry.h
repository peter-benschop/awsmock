//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_DELETEMESSAGEBATCHENTRY_H
#define AWSMOCK_DTO_SQS_DELETEMESSAGEBATCHENTRY_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

namespace AwsMock::Dto::SQS {

    struct DeleteMessageBatchEntry {

      /**
       * Entry ID
       */
      std::string id;

      /**
       * Receipt handle
       */
      std::string receiptHandle;

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
      friend std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchEntry &d);

    };

    typedef std::vector<DeleteMessageBatchEntry> DeleteMessageBatchEntries;

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_DELETEMESSAGEBATCHENTRY_H
