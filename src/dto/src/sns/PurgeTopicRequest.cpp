//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/PurgeTopicRequest.h>

namespace AwsMock::Dto::SNS {

    void PurgeTopicRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("topicArn", rootObject, topicArn);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string PurgeTopicRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("topicArn", topicArn);
            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string PurgeTopicRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PurgeTopicRequest &r) {
        os << "PurgeTopicRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
