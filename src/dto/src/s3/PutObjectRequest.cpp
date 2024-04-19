//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/PutObjectRequest.h>

namespace AwsMock::Dto::S3 {

  std::string PutObjectRequest::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("region", region);
      rootJson.set("bucket", bucket);
      rootJson.set("key", key);
      rootJson.set("md5sum", md5Sum);
      rootJson.set("contentType", contentType);
      rootJson.set("contentLength", contentLength);
      rootJson.set("owner", owner);
      rootJson.set("metadata", Core::JsonUtils::GetJsonObject(metadata));

      return Core::JsonUtils::ToJsonString(rootJson);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string PutObjectRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const PutObjectRequest &r) {
    os << "PutObjectRequest=" << r.ToJson();
    return os;
  }

} // namespace AwsMock::Dto::s3
