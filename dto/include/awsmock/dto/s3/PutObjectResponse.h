//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_PUTOBJECTRESPONSE_H
#define AWSMOCK_CORE_DTO_PUTOBJECTRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"

namespace AwsMock::Dto::S3 {

    class PutObjectResponse {

    public:

      /**
       * Constructor
       */
      PutObjectResponse() = default;

      void SetBucket(const std::string &bucket) { _bucket = bucket; }

      std::string GetBucket() { return _bucket; }

      void SetKey(const std::string &key) { _key = key; }

      std::string GetKey() { return _key; }

      void SetETag(const std::string &etag) { _etag = etag; }

      std::string GetETag() { return _etag; }

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
       * ETag
       */
      std::string _etag;

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &, const PutObjectResponse &);
    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_CORE_DTO_PUTOBJECTRESPONSE_H
