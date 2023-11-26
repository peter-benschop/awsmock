//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateUserPoolResponse.h>

namespace AwsMock::Dto::Cognito {

  std::string CreateUserPoolResponse::ToJson() const {

    try {
      Poco::JSON::Object rootObject;

      rootObject.set("Region", region);
      rootObject.set("Name", name);

      std::ostringstream os;
      rootObject.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string CreateUserPoolResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateUserPoolResponse &r) {
    os << "CreateUserPoolResponse={region='" << r.region << "', name=" << r.name << "}";
    return os;
  }
}