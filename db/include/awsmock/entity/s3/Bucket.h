//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_BUCKET_H
#define AWSMOCK_DB_ENTITY_S3_BUCKET_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/DateTime.h>

namespace AwsMock::Database::Entity::S3 {

    struct Bucket {

      /**
       * ID
       */
      long id = 0;

      /**
       * Bucket name
       */
      std::string name;

      /**
       * Bucket region
       */
      std::string region;

      /**
       * Bucket owner
       */
      std::string owner;

      /**
       * Creation date
       */
      Poco::DateTime created;

      /**
       * Last modification date
       */
      Poco::DateTime modified;
    };

    typedef struct Bucket Bucket;
    typedef std::vector<Bucket> BucketList;

} // namespace AwsMock::Database::S3::Entity

#endif //AWSMOCK_DB_ENTITY_S3_BUCKET_H
