//
// Created by vogje01 on 12/18/23.
//

#ifndef AWSMOCK_DTO_S3_OWNER_H
#define AWSMOCK_DTO_S3_OWNER_H

// C++ includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::S3 {

  struct Owner {

    /**
     * ID
     */
    std::string id;

    /**
     * Display name
     */
    std::string displayName;

    /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
    std::string ToString() const;

    /**
     * Stream provider.
     *
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Owner &r);

  };

} // namespace AwsMock::Dto::S3
#endif // AWSMOCK_DTO_S3_OWNER_H
