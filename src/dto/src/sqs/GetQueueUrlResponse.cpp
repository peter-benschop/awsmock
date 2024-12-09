//
// Created by vogje01 on 30/05/2023.
//

// AwsMock includes
#include <awsmock/dto/sqs/GetQueueUrlResponse.h>

namespace AwsMock::Dto::SQS {

    std::string GetQueueUrlResponse::ToXml() const {

        try {
            boost::property_tree::ptree root;
            root.add("GetQueueUrlResponse.GetQueueUrlResult.QueueUrl", queueUrl);
            root.add("GetQueueUrlResponse.ResponseMetadata.RequestId", Core::StringUtils::CreateRandomUuid());
            return Core::XmlUtils::ToXmlString(root);
        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetQueueUrlResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "QueueUrl", queueUrl);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void GetQueueUrlResponse::FromJson(const std::string &jsonString) {

        try {
            const value document = bsoncxx::from_json(jsonString);
            queueUrl = Core::Bson::BsonUtils::GetStringValue(document, "QueueUrl");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetQueueUrlResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetQueueUrlResponse &r) {
        os << "GetQueueUrlRequest={queueUrl='" << r.queueUrl << "'}";
        return os;
    }

}// namespace AwsMock::Dto::SQS
