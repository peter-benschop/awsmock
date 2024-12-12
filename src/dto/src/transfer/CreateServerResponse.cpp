
#include <awsmock/dto/transfer/CreateServerResponse.h>

namespace AwsMock::Dto::Transfer {

    std::string CreateServerResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "ServerId", serverId);
            Core::Bson::BsonUtils::SetStringValue(document, "Arn", arn);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
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
