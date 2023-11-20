//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_MESSAGEATTRIBUTE_H
#define AWSMOCK_DTO_SQS_MESSAGEATTRIBUTE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

namespace AwsMock::Dto::SQS {

  struct MessageAttribute {

    /**
     * MessageAttribute name
     */
    std::string attributeName;

    /**
     * MessageAttribute value
     */
    std::string attributeValue;

    /**
     * Logical data type
     */
    std::string type;

    /**
     * Transport data type
     */
    std::string transportType;

    bool operator<(const MessageAttribute &other) const;

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
    friend std::ostream &operator<<(std::ostream &os, const MessageAttribute &r);

  };

  typedef std::vector<MessageAttribute> MessageAttributeList;

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_MESSAGEATTRIBUTE_H
