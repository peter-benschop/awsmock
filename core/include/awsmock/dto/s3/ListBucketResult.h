//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DTO_S3_LISTBUCKETRESULT_H
#define AWSMOCK_DTO_S3_LISTBUCKETRESULT_H

// C++ Standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

namespace AwsMock::Dto::S3 {

    class Owner {

    private:

      /**
       * Display name
       */
      std::string _displayName;

      /**
       * ID
       */
      std::string _id;
    };

    class Content {

    private:

      /**
       * Checksum algorithms
       */
      std::vector<std::string> _checksumAlgorithms;

      /**
       * ETag
       */
      std::string _etag;

      /**
       * Key
       */
      std::string _key;

      /**
       * Last modified
       */
      std::string _lastModified;

      /**
       * Owner
       */
      Owner _owner;

      /**
       * Size
       */
      long _size;
    };

    class CommonPrefix {

    private:

      /**
       * Prefix
       */
      std::string _prefix;
    };

    class ListBucketResult {

    public:

      /**
       * Return XML string
       *
       * @return XML string representation.
       */
        std::string ToXml();

    private:

      /**
       * Truncation flag
       */
      bool _isTruncated;

      /**
       * Contents
       */
      std::vector<Content> contents;

      /**
       * Name
       */
      std::string _name;

      /**
       * Prefix
       */
      std::string _prefix;

      /**
       * Delimiter
       */
      std::string _delimiter;

      /**
       * Maximal keys
       */
      int _maxKeys;

      /**
       * Encoding type
       */
      std::string _encodingType;

      /**
       * Key count
       */
      int _keyCount;

      /**
       * Continuation token
       */
      std::string _continuationToken;

      /**
       * Next continuation token
       */
      std::string _nextContinuationToken;

      /**
       * Start after
       */
      std::string _startAfter;
    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_DTO_S3_LISTBUCKETRESULT_H
