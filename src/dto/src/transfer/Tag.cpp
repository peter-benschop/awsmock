//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/transfer/Tag.h>

namespace AwsMock::Dto::Transfer {

  std::string Tag::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Tag &r) {
    os << "Tag={key='" << r.key << "', value='" << r.value << "'}";
    return os;
  }

} // namespace AwsMock::Dto::Transfer
