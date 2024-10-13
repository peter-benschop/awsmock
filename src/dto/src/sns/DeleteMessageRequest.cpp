//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/DeleteMessageRequest.h>

namespace AwsMock::Dto::SNS {

    void DeleteMessageRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("messageId", rootObject, messageId);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DeleteMessageRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("messageId", messageId);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    [[nodiscard]] std::string DeleteMessageRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteMessageRequest &r) {
        os << "DeleteMessageRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
