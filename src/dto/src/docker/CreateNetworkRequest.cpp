//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/docker/CreateNetworkRequest.h>

namespace AwsMock::Dto::Docker {

    std::string CreateNetworkRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Name", name);
            Core::Bson::BsonUtils::SetStringValue(document, "Driver", driver);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateNetworkRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateNetworkRequest &r) {
        os << "CreateNetworkRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
