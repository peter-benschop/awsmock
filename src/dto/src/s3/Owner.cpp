//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/Owner.h>

namespace AwsMock::Dto::S3 {

  std::string Owner::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("id", id);
      rootJson.set("displayName", displayName);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::JsonException(exc.message());
    }
  }

  Poco::JSON::Object Owner::ToJsonObject() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("DisplayName", displayName);
      rootJson.set("Id", id);
      return rootJson;

    } catch (Poco::Exception &exc) {
      throw Core::JsonException(exc.message());
    }
  }

  std::string Owner::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Owner &o) {
    os << "Owner=" << o.ToJson();
    return os;
  }

} // namespace AwsMock::Dto::S3
