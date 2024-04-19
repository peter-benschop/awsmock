//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetMetadataResponse.h>

namespace AwsMock::Dto::S3 {

  std::string GetMetadataResponse::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("region", region);
      rootJson.set("bucket", bucket);
      rootJson.set("key", key);
      rootJson.set("md5sum", md5Sum);
      rootJson.set("contentType", contentType);
      rootJson.set("size", size);
      rootJson.set("metadata", Core::JsonUtils::GetJsonObject(metadata));

      return Core::JsonUtils::ToJsonString(rootJson);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string GetMetadataResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const GetMetadataResponse &r) {
    os << "GetMetadataResponse="<<r.ToJson();
    return os;
  }

} // namespace AwsMock::Dto::S3
