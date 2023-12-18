//
// Created by vogje01 on 12/18/23.
//

#ifndef AWSMOCK_DTO_S3_CONTENT_H
#define AWSMOCK_DTO_S3_CONTENT_H

// C++ includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// AwsMock includes
#include <awsmock/dto/s3/Owner.h>

namespace AwsMock::Dto::S3 {

  struct Content {

    /**
     * Checksum algorithms
     */
    std::vector <std::string> checksumAlgorithms;

    /**
     * ETag
     */
    std::string etag;

    /**
     * Key
     */
    std::string key;

    /**
     * Owner
     */
    Owner owner;

    /**
     * Size
     */
    long size = 0;

    /**
     * Storage class
     */
    std::string storageClass;

    /**
     * Last modified
     */
    std::string lastModified;

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
    friend std::ostream &operator<<(std::ostream &os, const Content &r);

  };

} // namespace AwsMock::Dto::S3

#endif // AWSMOCK_DTO_S3_CONTENT_H
