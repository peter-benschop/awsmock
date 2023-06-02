//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_ATTRIBUTE_H
#define AWSMOCK_DB_ENTITY_SQS_ATTRIBUTE_H

// C++ includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>

namespace AwsMock::Database::Entity::SQS {

    struct Attribute {

      /**
       * ID
       */
      long id;

      /**
       * Attribute name
       */
      std::string name;

      /**
       * Attribute value
       */
      std::string value;

      /**
       * Creation date
       */
      Poco::DateTime created;

      /**
       * Last modification date
       */
      Poco::DateTime modified;
    };

    typedef struct Attribute Attribute;
    typedef std::vector<Attribute> AttributeList;

} // namespace AwsMock::Database::Entity::S3

#endif // AWSMOCK_DB_ENTITY_SQS_ATTRIBUTE_H
