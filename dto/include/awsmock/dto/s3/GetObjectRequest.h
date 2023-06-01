//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_GETOBJECTREQUEST_H
#define AWSMOCK_CORE_DTO_GETOBJECTREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"

namespace AwsMock::Dto::S3 {

    class GetObjectRequest {

    public:

      /**
       * Constructor
       */
      GetObjectRequest() = default;

      void SetBucket(const std::string &bucket) { _bucket = bucket; }

      std::string GetBucket() { return _bucket; }

      void SetKey(const std::string &key) { _key = key; }

      std::string GetKey() { return _key; }

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
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &, const GetObjectRequest &);
    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_CORE_DTO_GETOBJECTREQUEST_H
