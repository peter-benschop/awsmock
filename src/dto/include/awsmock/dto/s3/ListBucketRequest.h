//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DTO_S3_LIST_BUCKET_REQUEST_H
#define AWSMOCK_DTO_S3_LIST_BUCKET_REQUEST_H

// C++ Standard includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::S3 {

  struct ListBucketRequest {

    /**
     * Region
     */
    std::string region;

    /**
     * Name
     */
    std::string name;

    /**
     * List type
     */
    int listType;

    /**
     * Prefix
     */
    std::string prefix;

    /**
     * Delimiter
     */
    std::string delimiter;

    /**
     * Encoding type
     */
    std::string encodingType;

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
    friend std::ostream &operator<<(std::ostream &os, const ListBucketRequest &r);

  };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_DTO_S3_LIST_BUCKET_REQUEST_H
