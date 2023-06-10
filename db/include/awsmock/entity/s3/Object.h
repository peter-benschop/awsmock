//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_OBJECT_H
#define AWSMOCK_DB_ENTITY_S3_OBJECT_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/DateTime.h>

namespace AwsMock::Database::Entity::S3 {

    struct Object {

      /**
       * ID
       */
      long id = 0;

      /**
       * Aws region name
       */
      std::string region;

      /**
       * Bucket name
       */
      std::string bucket;

      /**
       * Object key
       */
      std::string key;

      /**
       * Object owner
       */
      std::string owner;

      /**
       * Object size
       */
      long size;

      /**
       * Object MD5Sum
       */
      std::string md5sum;

      /**
       * Object content type
       */
      std::string contentType;

      /**
       * Creation date
       */
      Poco::DateTime created;

      /**
       * Last modification date
       */
      Poco::DateTime modified;

      /**
       * Converts the DTO to a MongoDB document
       *
       * @return DTO as MongoDB document.
       */
/*      [[nodiscard]] Poco::MongoDB::Document::Ptr ToDocument() const {
          Poco::MongoDB::Document::Ptr objectDoc = new Poco::MongoDB::Document();
          objectDoc->add("region", region);
          objectDoc->add("bucket", bucket);
          objectDoc->add("key", key);
          objectDoc->add("owner", owner);
          objectDoc->add("size", size);
          objectDoc->add("md5sum", md5sum);
          objectDoc->add("contentType", contentType);
          objectDoc->add("created", created.timestamp());
          objectDoc->add("modified", modified.timestamp());
          return objectDoc;
      };*/

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const Object &o) {
          os << "Object={id='" + std::to_string(o.id) + "' bucket='" + o.bucket + "' key='" + o.key + "' owner='" + o.owner + "' size='" + std::to_string(o.size) +
              "' md5sum='" + o.md5sum + "' contentType='" + o.contentType + "' created='"
              + Poco::DateTimeFormatter().format(o.created, Poco::DateTimeFormat::HTTP_FORMAT) +
              "' modified='" + Poco::DateTimeFormatter().format(o.created, Poco::DateTimeFormat::HTTP_FORMAT) + "'}";
          return os;
      }

    };

    typedef struct Object Object;
    typedef std::vector<Object> ObjectList;

}
// namespace AwsMock::Database::S3::Entity

#endif //AWSMOCK_DB_ENTITY_S3_OBJECT_H
