//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListQueueResponse.h>

namespace AwsMock::Dto::SQS {

    std::string ListQueuesResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;

            for (auto &it: queueList) {
                root.add("ListQueuesResponse.ListQueuesResult.QueueUrl", it.queueUrl);
            }
            root.add("ListQueuesResponse.ResponseMetadata.RequestId", Core::StringUtils::CreateRandomUuid());
            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    std::string ListQueuesResponse::ToJson() const {

        try {
            document document;
            if (!queueList.empty()) {
                array jsonArray;
                for (const auto &queue: queueList) {
                    jsonArray.append(queue.queueUrl);
                }
                document.append(kvp("QueueUrls", jsonArray));
            }
            Core::Bson::BsonUtils::SetStringValue(document, "NextToken", nextToken);
            Core::Bson::BsonUtils::SetLongValue(document, "Total", total);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    std::string ListQueuesResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListQueuesResponse &r) {
        os << "ListQueuesResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
