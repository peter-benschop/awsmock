//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/Environment.h>

namespace AwsMock::Database::Entity::Lambda {

  void Environment::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    auto varDoc = mResult.value()["variables"].get_array();
    for (auto &v : varDoc.value) {
      for (auto &it : v.get_document().value) {
        variables[std::string{it.key()}] = it.get_string().value;
      }
    }
  }
}