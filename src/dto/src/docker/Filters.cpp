//
// Created by vogje01 on 1/20/24.
//

#include <awsmock/dto/docker/Filters.h>

namespace AwsMock::Dto::Docker {

  std::string Filters::ToJson() {
    try {
      Poco::JSON::Object rootObject;

      Poco::JSON::Array filterArray;
      for (const auto &filter : filters) {
        Poco::JSON::Object filterObject;
        filterObject.set(filter.name, filter.value);
        filterArray.add(filterObject);
      }

      rootObject.set("reference", filterArray);

      std::ostringstream os;
      rootObject.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string Filters::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Filters &p) {
    os << "Filters={[";
    for (const auto &filter : p.filters) {
      os << filter.name << "='" << filter.value << "', ";
    }
    os.seekp(-2, std::ostream::cur);
    os << "]}";
    return os;
  }

}