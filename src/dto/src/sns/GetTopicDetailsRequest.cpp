//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/GetTopicDetailsRequest.h>

namespace AwsMock::Dto::SNS {

    void GetTopicDetailsRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("topicArn", rootObject, topicArn);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GetTopicDetailsRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("topicArn", topicArn);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    [[nodiscard]] std::string GetTopicDetailsRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetTopicDetailsRequest &r) {
        os << "GetTopicDetailsRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
