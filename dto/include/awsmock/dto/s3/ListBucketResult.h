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

// AwsMock includes
#include <awsmock/entity/s3/Object.h>

namespace AwsMock::Dto::S3 {

    class Owner {

    public:

      /**
       * Returns the display name
       *
       * @return display name
       */
      std::string GetDisplayName() { return _displayName; }

      /**
       * Sets the display name
       *
       * @param displayName display name
       */
      void SetDisplayName(const std::string &displayName) { _displayName = displayName; }

      /**
       * Returns the display name
       *
       * @return ID
       */
      std::string GetId() { return _id; }

      /**
       * Sets the ID
       *
       * @param id ID
       */
      void SetId(const std::string &id) { _id = id; }

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

    public:

      /**
       * Returns the checksum algorithms.
       *
       * @return checksum algorithms
       */
      std::vector<std::string> GetChecksumAlgorithms() { return _checksumAlgorithms; }

      /**
       * Returns the ETag
       *
       * @return ETag
       */
      std::string GetEtag() { return _etag; }

      /**
       * Sets the ETag
       *
       * @param ETag AWS ETag
       */
      void SetEtag(const std::string &etag) { _etag = etag; }

      /**
       * Returns the key
       *
       * @return object key
       */
      std::string GetKey() { return _key; }

      /**
       * Sets the key
       *
       * @param object key
       */
      void SetKey(const std::string &key) { _key = key; }

      /**
       * Returns the last modified
       *
       * @return last modified
       */
      std::string GetLastModified() { return _lastModified; }

      /**
       * Returns the last modified
       *
       * @return last modified
       */
      void SetLastModified(const std::string &lastModified) { _lastModified = lastModified; }

      /**
       * Returns the owner
       *
       * @return owner
       */
      Owner GetOwner() { return _owner; }

      /**
       * Sets the owner
       *
       * @param owner object owner
       */
      void SetOwner(const Owner &owner) { _owner = owner; }

      /**
       * Returns the size
       *
       * @return size
       */
      [[nodiscard]] int GetSize() const { return _size; }

      /**
       * Returns the last modified
       *
       * @return last modified
       */
      void SetSize(int size) { _size = size; }

      /**
       * Returns the storage class
       *
       * @return storage class
       */
      std::string GetStorageClass() { return _storageClass; }

      /**
       * Sets the storage class
       *
       * @param storageClass storage class
       */
      void SetStorageClass(const std::string &storageClass) {  _storageClass = storageClass; }

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
      long _size = 0;

      /**
       * Storage class
       */
      std::string _storageClass;
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
       * Constructor.
       *
       * @param bucket nucket name
       * @param objectList list of S3 objects
       */
      ListBucketResult(const std::string &bucket, Database::Entity::S3::ObjectList objectList);

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
      bool _isTruncated = false;

      /**
       * Contents
       */
      std::vector<Content> _contents;

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
      int _maxKeys = 1000;

      /**
       * Encoding type
       */
      std::string _encodingType;

      /**
       * Key count
       */
      int _keyCount = 0;

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
