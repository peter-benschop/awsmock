//
// Created by vogje01 on 13/10/2023.
//

#ifndef AWSMOCK_CORE_DTO_PUTBUCKETVERSIONINGREQUEST_H
#define AWSMOCK_CORE_DTO_PUTBUCKETVERSIONINGREQUEST_H

// C++ standard includes
#include <map>
#include <sstream>
#include <string>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"

namespace AwsMock::Dto::S3 {

    struct PutBucketVersioningRequest {

        /**
     * AWS region
     */
        std::string region;

        /**
     * AWS user
     */
        std::string user;

        /**
     * Bucket name
     */
        std::string bucket;

        /**
     * Status
     */
        std::string status;
        /**
     * Constructor
     *
     * @param xmlString XML string
     */
        explicit PutBucketVersioningRequest(const std::string &xmlString);

        /**
     * Convert from XML representation
     *
     * @param xmlString XML string
     */
        void FromXml(const std::string &xmlString);

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
        friend std::ostream &operator<<(std::ostream &os, const PutBucketVersioningRequest &r);
    };

}// namespace AwsMock::Dto::S3

#endif//AWSMOCK_CORE_DTO_PUTBUCKETVERSIONINGREQUEST_H
