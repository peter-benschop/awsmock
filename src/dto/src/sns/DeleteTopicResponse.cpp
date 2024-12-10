//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/DeleteTopicResponse.h>

namespace AwsMock::Dto::SNS {

    std::string DeleteTopicResponse::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "RequestId", requestId);
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteTopicResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;
            root.add("DeleteTopicResponse.ResponseMetadata.RequestId", requestId);

            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteTopicResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteTopicResponse &r) {
        os << "DeleteTopicResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
