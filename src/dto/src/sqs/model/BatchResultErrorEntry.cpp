//
// Created by vogje01 on 7/6/24.
//

#include <awsmock/dto/sqs/model/BatchResultErrorEntry.h>

namespace AwsMock::Dto::SQS {

    std::string BatchResultErrorEntry::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object BatchResultErrorEntry::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Code", code);
            rootJson.set("Id", id);
            rootJson.set("SenderFault", senderFault);
            rootJson.set("Message", message);
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    [[nodiscard]] std::string BatchResultErrorEntry::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const BatchResultErrorEntry &r) {
        os << "BatchResultErrorEntry=" + r.ToJson();
        return os;
    }
};// namespace AwsMock::Dto::SQS
