//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/ListNetworkResponse.h>

namespace AwsMock::Dto::Docker {

    void ListNetworkResponse::FromJson(const std::string &jsonString) {

        try {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);
            Poco::JSON::Array::Ptr rootArray = result.extract<Poco::JSON::Array::Ptr>();
            if (rootArray != nullptr) {
                for (const auto &it: *rootArray) {
                    Network network;
                    network.FromJson(it.extract<Poco::JSON::Object::Ptr>());
                    networkList.push_back(network);
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListNetworkResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;

            Poco::JSON::Array networkArray;
            for (const auto &network: networkList) {
                networkArray.add(network.ToJsonObject());
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListNetworkResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListNetworkResponse &n) {
        os << "ListNetworkResponse=" << n.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
