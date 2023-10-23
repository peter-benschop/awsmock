//
// Created by vogje01 on 03/09/2023.
//

#ifndef AWSMOCK_ENTITY_LAMBDA_ENVIRONMENT_H
#define AWSMOCK_ENTITY_LAMBDA_ENVIRONMENT_H

// C++ includes
#include <string>
#include <vector>
#include <sstream>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

namespace AwsMock::Database::Entity::Lambda {

    struct Environment {

      /**
       * Variables
       */
      std::vector <std::pair<std::string, std::string>> variables;

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      void FromDocument(mongocxx::stdx::optional <bsoncxx::document::view> mResult);

    };

} // namespace AwsMock::Database::Entity::lambda {

#endif // AWSMOCK_ENTITY_LAMBDA_ENVIRONMENT_H
