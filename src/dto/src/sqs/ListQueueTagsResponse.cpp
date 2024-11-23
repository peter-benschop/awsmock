//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListQueueTagsResponse.h>

namespace AwsMock::Dto::SQS {

    std::string ListQueueTagsResponse::ToJson() const {

        try {
            Poco::JSON::Object queueTagsObject;
            for (const auto &tag: tags) {
                queueTagsObject.set(tag.first, tag.second);
            }

            Poco::JSON::Object rootJson;
            rootJson.set("Tags", queueTagsObject);
            rootJson.set("Total", total);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListQueueTagsResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListQueueTagsResponse &r) {
        os << "ListQueueTagsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
