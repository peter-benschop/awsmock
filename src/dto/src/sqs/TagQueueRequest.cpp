//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/TagQueueRequest.h>

namespace AwsMock::Dto::SQS {

    void TagQueueRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Get queue URL
            Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);

            // Get the tags
            Poco::JSON::Object::Ptr jsonTagsObject = rootObject->getObject("Tags");
            for (int i = 0; i < jsonTagsObject->getNames().size(); i++) {
                std::string value;
                std::string key = jsonTagsObject->getNames()[i];
                Core::JsonUtils::GetJsonValueString(key, jsonTagsObject, value);
                tags[key] = value;
            }

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string TagQueueRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TagQueueRequest &t) {
        os << "TagQueueRequest={region='" << t.region << "', queueUrl='" << t.queueUrl << "', tags=[";
        for (const auto &tag: t.tags) {
            os << tag.first << "=" << tag.second << ", ";
        }
        os.seekp(-2, std::ostream::cur);
        os << "]}";
        return os;
    }

}// namespace AwsMock::Dto::SQS
