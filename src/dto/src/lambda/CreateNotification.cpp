//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/dto/lambda/CreateNotification.h>

namespace AwsMock::Dto::Lambda {

  CreateNotification::CreateNotification(const std::string &zipFileContent, const std::string &functionId) {
    this->zipFileContent = zipFileContent;
    this->functionId = functionId;
  }

  std::string CreateNotification::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateNotification &f) {
    os << "CreateNotification={functionId='" << f.functionId << "}";
    return os;
  }
}
