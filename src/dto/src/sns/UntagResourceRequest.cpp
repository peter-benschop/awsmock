//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/UntagResourceRequest.h>

namespace AwsMock::Dto::SNS {

    std::string UntagResourceRequest::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "RequestId", Core::StringUtils::CreateRandomUuid());

            if(tags.empty()) {
                array jsonArray;
                for(const auto& tag : tags) {
                    document tagDoc;
                    jsonArray.append(tag);
                }
                rootDocument.append(kvp("Tags", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UntagResourceRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UntagResourceRequest &t) {
        os << "UntagResourceRequest="+t.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
