//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListMessageCountersResponse.h>

namespace AwsMock::Dto::SQS {

    std::string ListMessageCountersResponse::ToJson() const {

        try {
            Poco::JSON::Array messageArrayJson;
            for (const auto &message: messages) {
                messageArrayJson.add(message.ToJsonObject());
            }

            Poco::JSON::Object rootJson;
            rootJson.set("Messages", messageArrayJson);
            rootJson.set("Total", total);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListMessageCountersResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListMessageCountersResponse &r) {
        os << "ListMessageCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
