//
// Created by vogje01 on 12/18/23.
//

#ifndef AWSMOCK_DTO_TRANSFER_TAG_H
#define AWSMOCK_DTO_TRANSFER_TAG_H

// C++ includes
#include <string>
#include <sstream>
#include <vector>

namespace AwsMock::Dto::Transfer {

  struct Tag {

    /**
     * Key
     */
    std::string key;

    /**
     * Value
     */
    std::string value;

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
    friend std::ostream &operator<<(std::ostream &os, const Tag &r);

  };

  typedef std::vector<Tag> TagList;

} // namespace AwsMock::Dto::Transfer

#endif // AWSMOCK_DTO_TRANSFER_TAG_H
