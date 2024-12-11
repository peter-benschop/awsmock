
#include <awsmock/dto/transfer/CreateServerResponse.h>

namespace AwsMock::Dto::Transfer {

    std::string CreateServerResponse::ToJson() const {

        // Todo:
        /*
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("ServerId", serverId);
            rootJson.set("Arn", arn);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    std::string CreateServerResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateServerResponse &r) {
        os << "CreateServerResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Transfer
