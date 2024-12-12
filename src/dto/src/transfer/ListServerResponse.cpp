//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/ListServerResponse.h>

namespace AwsMock::Dto::Transfer {

    std::string ListServerResponse::ToJson() const {

        try {

            document document;
            if (servers.empty()) {
                array jsonArray;
                for (const auto &server: servers) {
                    jsonArray.append(server.ToDocument());
                }
                document.append(kvp("Servers", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListServerResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListServerResponse &r) {
        os << "ListServerResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer
