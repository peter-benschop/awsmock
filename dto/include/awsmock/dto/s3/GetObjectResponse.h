//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_GETOBJECTRESPONSE_H
#define AWSMOCK_CORE_DTO_GETOBJECTRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"

namespace AwsMock::Dto::S3 {

    class GetObjectResponse {

    public:

      void SetBucket(const std::string &bucket) { _bucket = bucket; }

      std::string GetBucket() { return _bucket; }

      void SetKey(const std::string &key) { _key = key; }

      std::string GetKey() { return _key; }

      void SetSize(long size) { _size = size; }

      long GetSize() { return _size; }

      void SetFilename(std::string filename) { _filename = filename; };

      std::string GetFilename() { return _filename; }

      void SetContentType(const std::string &contentType) { _contentType = contentType; };

      std::string GetContentType() { return _contentType; }

      void SetLastModified(const std::string &lastModified) { _lastModified = lastModified; };

      std::string GetLastModified() { return _lastModified; }

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
       * Content length
       */
      long _size;

      /**
       * File name
       */
      std::string _filename;

      /**
       * Content type
       */
      std::string _contentType;

      /**
       * Last modified
       */
      std::string _lastModified;

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &, const GetObjectResponse &);
    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_CORE_DTO_GETOBJECTRESPONSE_H
