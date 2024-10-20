//
// Created by vogje01 on 7/6/24.
//

#include <awsmock/dto/sqs/model/DeleteMessageBatchResultEntry.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteMessageBatchResultEntry::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object DeleteMessageBatchResultEntry::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Id", id);
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    [[nodiscard]] std::string DeleteMessageBatchResultEntry::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchResultEntry &r) {
        os << "DeleteMessageBatchResultEntry=" + r.ToJson();
        return os;
    }
};// namespace AwsMock::Dto::SQS
