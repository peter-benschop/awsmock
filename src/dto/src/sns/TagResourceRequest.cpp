//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/TagResourceRequest.h>

namespace AwsMock::Dto::SNS {

    std::string TagResourceRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "RequestId", Core::StringUtils::CreateRandomUuid());
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string TagResourceRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TagResourceRequest &r) {
        os << "TagResourceRequest=" + r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
