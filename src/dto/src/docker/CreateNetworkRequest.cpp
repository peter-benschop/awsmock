//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/docker/CreateNetworkRequest.h>

namespace AwsMock::Dto::Docker {

    std::string CreateNetworkRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Name", name);
            rootJson.set("Driver", driver);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateNetworkRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateNetworkRequest &r) {
        os << "CreateNetworkRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
