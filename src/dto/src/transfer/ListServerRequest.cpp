//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/ListServerRequest.h>

namespace AwsMock::Dto::Transfer {

  std::string ListServerRequest::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Region", region);
      rootJson.set("MaxResults", maxResults);
      rootJson.set("NextToken", nextToken);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  void ListServerRequest::FromJson(const std::string &body) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(body);
    Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      // Get root values
      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueInt("MaxResults", rootObject, maxResults);
      Core::JsonUtils::GetJsonValueString("NextToken", rootObject, nextToken);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string ListServerRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const ListServerRequest &r) {
    os << "ListServerRequest={region='" << r.region << "' maxResults='" << r.maxResults << "' nextToken='" << r.nextToken << "'}";
    return os;
  }

} // namespace AwsMock::Dto::lambda
