//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/transfer/IdentityProviderDetails.h>

namespace AwsMock::Dto::Transfer {

  std::string IdentityProviderDetails::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const IdentityProviderDetails &r) {
    os << "IdentityProviderDetails={directoryId='" << r.directoryId << "' function='" << r.function << "' invocationRole='" << r.invocationRole << "', sftpAuthenticationMethods='" << r.sftpAuthenticationMethods << "', url='" << r.url << "'}";
    return os;
  }

} // namespace AwsMock::Dto::Transfer
