//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_GETMETADATARESPONSE_H
#define AWSMOCK_DTO_S3_GETMETADATARESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"

namespace AwsMock::Dto::S3 {

    class GetMetadataResponse {

    public:

      /**
       * Constructor
       */
      GetMetadataResponse() = default;

      void SetBucket(const std::string &bucket) { _bucket = bucket; }

      std::string GetBucket() { return _bucket; }

      void SetKey(const std::string &key) { _key = key; }

      std::string GetKey() { return _key; }

      void SetMd5Sum(const std::string &md5Sum) { _md5Sum = md5Sum; }

      std::string GetMd5Sum() { return _md5Sum; }

      void SetContentType(const std::string &contentType) { _contentType = contentType; }

      std::string GetContentType() { return _contentType; }

      void SetSize(long size) { _size = size; }

      long GetSize() { return _size; }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const;

    private:

      /**
       * Bucket
       */
      std::string _bucket;

      /**
       * Key
       */
      std::string _key;

      /**
       * MD5 sum
       */
      std::string _md5Sum;

      /**
       * Content type
       */
      std::string _contentType;

      /**
       * Size
       */
      long _size;

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &, const GetMetadataResponse &);
    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_DTO_S3_GETMETADATARESPONSE_H
