//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/ListMessagesResponse.h>

namespace AwsMock::Dto::SNS {

    std::string ListMessagesResponse::ToJson() const {
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("total", total);

            Poco::JSON::Array jsonArray;
            for (const auto &message: messageList) {
                jsonArray.add(message.ToJsonObject());
            }

            rootJson.set("messages", jsonArray);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListMessagesResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListMessagesResponse &r) {
        os << "ListMessagesResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
