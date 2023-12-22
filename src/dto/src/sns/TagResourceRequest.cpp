//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/TagResourceRequest.h>

namespace AwsMock::Dto::SNS {

  std::string TagResourceRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const TagResourceRequest &t) {
    os << "TagResourceRequest={region='" << t.region << "', resourceArn='" << t.resourceArn << "', tags=[";
    for(const auto &tag:t.tags) {
      os << tag.first << "=" << tag.second << ", ";
    }
    os.seekp(-2, std::ostream::cur);
    os << "]}";
    return os;
  }

} // namespace AwsMock::Dto::SNS
