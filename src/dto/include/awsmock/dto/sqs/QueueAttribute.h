//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_QUEUEATTRIBUTE_H
#define AWSMOCK_DTO_SQS_QUEUEATTRIBUTE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

namespace AwsMock::Dto::SQS {

    struct QueueAttribute {

      /**
       * MessageAttribute name
       */
      std::string attributeName;

      /**
       * MessageAttribute value
       */
      std::string attributeValue;

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
      friend std::ostream &operator<<(std::ostream &os, const QueueAttribute &r);

    };

    typedef std::vector<QueueAttribute> QueueAttributeList;

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_QUEUEATTRIBUTE_H
