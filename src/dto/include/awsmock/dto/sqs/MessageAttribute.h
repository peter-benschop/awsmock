//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_MESSAGEATTRIBUTE_H
#define AWSMOCK_DTO_SQS_MESSAGEATTRIBUTE_H

// C++ standard includes
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>

// AwsMock includes
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/dto/sqs/MessageAttributeDataType.h>

namespace AwsMock::Dto::SQS {

  struct MessageAttribute {

    /**
     * Message attribute name
     */
    std::string name;

    /**
     * Message attribute string value
     */
    std::string stringValue;

    /**
     * Message attribute binary value
     */
    unsigned char* binaryValue;

    /**
     * Logical data type
     */
    MessageAttributeDataType type;

    /**
     * Transport data type
     */
    std::string transportType;

    /**
     * Returns the MD5 sum of all attributes.
     *
     * @param attributes vector of attributes
     * @return MD5 sum of attributes string
     */
    static std::string GetMd5Attributes(const std::vector<MessageAttribute> &attributes);

    /**
     * Returns a integer as byte array and fill it in the given byte array at position offset.
     *
     * @param n integer value
     * @param bytes output byte array
     * @param offset offset of the output byte array
     */
    static void GetIntAsByteArray(int n, unsigned char *bytes, int offset);

    /**
     * Name comparator
     *
     * @param other
     * @return
     */
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
