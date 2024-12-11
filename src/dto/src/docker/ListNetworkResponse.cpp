//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/ListNetworkResponse.h>

namespace AwsMock::Dto::Docker {

    void ListNetworkResponse::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);

            for (const auto &element: document.view()) {
                Network network;
                network.FromDocument(element.get_document().view());
                networkList.push_back(network);
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListNetworkResponse::ToJson() const {

        try {

            array document;

            if (!networkList.empty()) {
                for (const auto &network: networkList) {
                    document.append(network.ToDocument());
                }
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListNetworkResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListNetworkResponse &n) {
        os << "ListNetworkResponse=" << n.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
