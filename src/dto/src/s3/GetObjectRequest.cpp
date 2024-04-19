//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetObjectRequest.h>

namespace AwsMock::Dto::S3 {

  std::string GetObjectRequest::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("region", region);
      rootJson.set("bucket", bucket);
      rootJson.set("key", key);
      rootJson.set("versionId", versionId);
      rootJson.set("min", min);
      rootJson.set("max", max);

      return Core::JsonUtils::ToJsonString(rootJson);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string GetObjectRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const GetObjectRequest &r) {
    os << "GetObjectRequest=" << r.ToJson();
    return os;
  }

} // namespace AwsMock::Dto::S3
