//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_LIST_ALL_BUCKET_RESPONSE_H
#define AWSMOCK_DTO_S3_LIST_ALL_BUCKET_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/Text.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/XML/XMLWriter.h>

// AwsMock includes
#include <awsmock/entity/s3/Bucket.h>

namespace AwsMock::Dto::S3 {

    struct ListAllBucketResponse {

        /**
         * List of buckets
         */
        Database::Entity::S3::BucketList bucketList;

        /**
         * Convert to XML representation
         *
         * @return XML string
         */
        [[nodiscard]] std::string ToXml() const;

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
        friend std::ostream &operator<<(std::ostream &os, const ListAllBucketResponse &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_LIST_ALL_BUCKET_RESPONSE_H
