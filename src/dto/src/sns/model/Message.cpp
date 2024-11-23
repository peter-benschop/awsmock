//
// Created by vogje01 on 03/10/2023.
//

#include "awsmock/dto/sns/model/Message.h"

namespace AwsMock::Dto::SNS {

    std::string Message::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    Poco::JSON::Object Message::ToJsonObject() const {

        Poco::JSON::Object rootObject;
        try {

            rootObject.set("Region", region);
            rootObject.set("TopicArn", topicArn);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
        return rootObject;
    }

    std::string Message::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Message &r) {
        os << "Message=" + r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SNS
