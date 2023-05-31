//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_COMPLETEMULTIPARTUPLOAD_H
#define AWSMOCK_DTO_S3_COMPLETEMULTIPARTUPLOAD_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

namespace AwsMock::Dto::S3 {

    class CompleteMultipartUploadResult {

    public:

      /**
       * Constructor
       */
      CompleteMultipartUploadResult(const std::string &location, const std::string &bucket, const std::string &key, const std::string &eTag);

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      std::string ToXml();

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const;

    private:

      /**
       * AWS location
       */
      std::string _location;

      /**
       * Bucket name
       */
      std::string _bucket;

      /**
       * Key name
       */
      std::string _key;

      /**
       * ETag
       */
      std::string _etag;

      /**
       * Checksum CRC32
       */
      std::string _checksumCrc32;

      /**
       * Checksum CRC32C
       */
      std::string _checksumCrc32c;

      /**
       * Checksum SHA1
       */
      std::string _checksumSha1;

      /**
       * Checksum SHA256
       */
      std::string _checksumSha256;

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &, const CompleteMultipartUploadResult &);
    };

 } // namespace AwsMock::Dto

#endif //AWSMOCK_DTO_S3_COMPLETEMULTIPARTUPLOAD_H
