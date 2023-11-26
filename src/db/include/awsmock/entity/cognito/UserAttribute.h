//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DB_ENTITY_COGNITO_USERATTRIBUTE_H
#define AWSMOCK_DB_ENTITY_COGNITO_USERATTRIBUTE_H

// C++ includes
#include <string>
#include <vector>

namespace AwsMock::Database::Entity::Cognito {

  struct Attribute {

    /**
     * Name
     */
    std::string name;

    /**
     * Value
     */
    std::string value;
  };

  typedef std::vector<Attribute> AttributeList;
}

#endif // AWSMOCK_DB_ENTITY_COGNITO_USERATTRIBUTE_H
