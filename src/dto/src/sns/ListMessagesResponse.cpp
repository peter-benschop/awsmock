//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/ListMessagesResponse.h>

namespace AwsMock::Dto::SNS {

    std::string ListMessagesResponse::ToJson() const {

        try {

            document document;

            if (!messageList.empty()) {
                array jsonArray;
                for (const auto &message: messageList) {
                    jsonArray.append(message.ToDocument());
                }
                document.append(kvp("messages", jsonArray));
            }

            Core::Bson::BsonUtils::SetLongValue(document, "total", total);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListMessagesResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListMessagesResponse &r) {
        os << "ListMessagesResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
