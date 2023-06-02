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
    };

    typedef struct Object Object;
    typedef std::vector<Object> ObjectList;

}
// namespace AwsMock::Database::S3::Entity

#endif //AWSMOCK_DB_ENTITY_S3_OBJECT_H
