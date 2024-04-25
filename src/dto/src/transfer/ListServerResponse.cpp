//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/ListServerResponse.h>

namespace AwsMock::Dto::Transfer {

    std::string ListServerResponse::ToJson() const {

        try {

            Poco::JSON::Array serversJsonArray;
            for (const auto &server: servers) {
                serversJsonArray.add(server.ToJsonObject());
            }

            Poco::JSON::Object rootJson;
            rootJson.set("Servers", serversJsonArray);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListServerResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListServerResponse &r) {
        os << "ListServerResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer
