//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/ListServerResponse.h>

namespace AwsMock::Dto::Transfer {

    std::string ListServerResponse::ToJson() {

      try {
        Poco::JSON::Object rootJson;
        //rootJson.set("Region", region);
        //rootJson.set("NextToken", null);

        Poco::JSON::Array serversJsonArray;
        for (const auto &server : servers) {
          serversJsonArray.add(server.ToJsonObject());
        }
        rootJson.set("Servers", serversJsonArray);

        std::ostringstream os;
        rootJson.stringify(os);
        return os.str();

      } catch (Poco::Exception &exc) {
        throw Core::ServiceException(exc.message(), 500);
      }
    }

    std::string ListServerResponse::ToString() const {
      std::stringstream ss;
      ss << (*this);
      return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListServerResponse &r) {
      os << "ListServerResponse={region='" << r.region << "' nextToken='" << r.nextToken << "' servers={'";
      for (auto &server : r.servers) {
        os << server.ToString();
      }
      return os;
    }

} // namespace AwsMock::Dto::Transfer
