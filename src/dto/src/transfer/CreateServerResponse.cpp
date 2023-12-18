
#include <awsmock/dto/transfer/CreateServerResponse.h>

namespace AwsMock::Dto::Transfer {

  std::string CreateServerResponse::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Region", region);
      rootJson.set("ServerId", serverId);
      rootJson.set("Arn", arn);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string CreateServerResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateServerResponse &r) {
    os << "CreateServerResponse={region='" << r.region << "' serverId='" << r.serverId << "' arn='" << r.arn;
    return os;
  }

} // namespace AwsMock::Dto::Transfer
