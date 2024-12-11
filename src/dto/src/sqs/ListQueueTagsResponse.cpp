//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListQueueTagsResponse.h>

namespace AwsMock::Dto::SQS {

    std::string ListQueueTagsResponse::ToJson() const {

        try {
            document rootDocument;

            if (!tags.empty()) {
                document tagsArrayJson;
                for (const auto &[fst, snd]: tags) {
                    tagsArrayJson.append(kvp(fst, snd));
                }
                rootDocument.append(kvp("Tags", tagsArrayJson));
            }
            Core::Bson::BsonUtils::SetLongValue(rootDocument, "Total", total);
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
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
