//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_GETMETADATAREQUEST_H
#define AWSMOCK_DTO_S3_GETMETADATAREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"

namespace AwsMock::Dto::S3 {

    class GetMetadataRequest {

    public:

      /**
       * Constructor
       */
      GetMetadataRequest() = default;

      void SetBucket(const std::string &bucket) { _bucket = bucket; }

      std::string GetBucket() { return _bucket; }

      void SetKey(const std::string &key) { _key = key; }

      std::string GetKey() { return _key; }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      std::string ToString() const;

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
      friend std::ostream &operator<<(std::ostream &, const GetMetadataRequest &);
    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_DTO_S3_GETMETADATAREQUEST_H
