//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/EphemeralStorage.h>

namespace AwsMock::Database::Entity::Lambda {

  void EphemeralStorage::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    size = mResult.value()["size"].get_int64();
  }

  Poco::JSON::Object EphemeralStorage::ToJsonObject() const {

    Poco::JSON::Object jsonObject;
    jsonObject.set("size", size);
    return jsonObject;
  }

  std::string EphemeralStorage::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const EphemeralStorage &m) {
    os << "EphemeralStorage={size='" << m.size << "'}";
    return os;
  }
}