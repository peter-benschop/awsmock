//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/core/StringUtils.h>
#include <awsmock/dto/sqs/CreateQueueResponse.h>

namespace AwsMock::Dto::SQS {

    std::string CreateQueueResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "QueueName", name);
            Core::Bson::BsonUtils::SetStringValue(document, "QueueUrl", queueUrl);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void CreateQueueResponse::FromJson(const std::string &jsonString) {

        try {

            boost::property_tree::ptree pt;
            read_xml(jsonString, pt);
            name = pt.get<std::string>("QueueName");
            queueUrl = pt.get<std::string>("QueueUrl");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateQueueResponse::ToXml() const {

        try {

            boost::property_tree::ptree pt;
            pt.put("CreateQueueResponse.CreateQueueResult.QueueName", name);
            pt.put("CreateQueueResponse.CreateQueueResult.QueueUrl", queueUrl);
            pt.put("CreateQueueResponse.ResponseMetadata.RequestId", Core::StringUtils::CreateRandomUuid());
            return Core::XmlUtils::ToXmlString(pt);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateQueueResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateQueueResponse &r) {
        os << "CreateQueueResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
