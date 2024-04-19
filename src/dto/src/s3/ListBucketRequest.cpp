//
// Created by vogje01 on 31/05/2023.
//

#include <awsmock/dto/s3/ListBucketRequest.h>

namespace AwsMock::Dto::S3 {

  std::string ListBucketRequest::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("region", region);
      rootJson.set("prefix", prefix);
      rootJson.set("listType", listType);
      rootJson.set("delimiter", delimiter);
      rootJson.set("encodingType", encodingType);

      return Core::JsonUtils::ToJsonString(rootJson);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string ListBucketRequest::ToString() const {
      std::stringstream ss;
      ss << (*this);
      return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListBucketRequest &r) {
      os << "ListBucketRequest=" << r.ToJson();
      return os;
    }

} // namespace AwsMock::Dto::S3
