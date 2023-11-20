//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DTO_S3_LISTBUCKETREQUEST_H
#define AWSMOCK_DTO_S3_LISTBUCKETREQUEST_H

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
    friend std::ostream &operator<<(std::ostream &os, const ListBucketRequest &r) {
      os << "ListBucketRequest={name='" << r.name << "' prefix='" << r.prefix << "' listType='" << r.listType << "' delimiter='" << r.delimiter
         << "' encodingType='" << r.encodingType << "'}";
      return os;
    }

  };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_DTO_S3_LISTBUCKETREQUEST_H
