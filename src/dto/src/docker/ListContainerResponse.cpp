//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/ListContainerResponse.h>

namespace AwsMock::Dto::Docker {

  ListContainerResponse::ListContainerResponse(const std::string &body) {
    FromJson(body);
  }

  void ListContainerResponse::FromJson(const std::string &body) {

    try {
      Poco::JSON::Parser parser;
      Poco::Dynamic::Var result = parser.parse(body);
      Poco::JSON::Array::Ptr rootArray = result.extract<Poco::JSON::Array::Ptr>();
      if (rootArray != nullptr) {
        for (const auto &it : *rootArray) {
          Container container;
          container.FromJson(it.extract<Poco::JSON::Object::Ptr>());
          containerList.push_back(container);
        }
      }

    } catch (Poco::Exception &exc) {
      std::cerr << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), 500);
    }
  }

} // namespace AwsMock::Dto::Docker
