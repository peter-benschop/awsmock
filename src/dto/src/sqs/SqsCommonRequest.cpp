//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SqsCommonRequest.h>

namespace AwsMock::Dto::SQS {

    std::string SqsCommonRequest::ToJson() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "RequestId", requestId);
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    void SqsCommonRequest::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            requestId = Core::Bson::BsonUtils::GetStringValue(document, "RequestId");
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    std::string SqsCommonRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SqsCommonRequest &r) {
        os << "SqsCommonRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
