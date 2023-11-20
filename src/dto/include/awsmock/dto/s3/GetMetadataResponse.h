//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_GETMETADATARESPONSE_H
#define AWSMOCK_DTO_S3_GETMETADATARESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"

namespace AwsMock::Dto::S3 {

  struct GetMetadataResponse {

    /**
     * Bucket
     */
    std::string bucket;

    /**
     * Key
     */
    std::string key;

    /**
     * MD5 sum
     */
    std::string md5Sum;

    /**
     * Content type
     */
    std::string contentType;

    /**
     * Size
     */
    long size;

    /**
     * Metadata
     */
    std::map<std::string, std::string> metadata;

    /**
     * Created
     */
    Poco::DateTime created;

    /**
     * Last modified
     */
    Poco::DateTime modified;

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
    friend std::ostream &operator<<(std::ostream &os, const GetMetadataResponse &r);

  };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_DTO_S3_GETMETADATARESPONSE_H
