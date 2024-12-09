//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/PublishResponse.h>

namespace AwsMock::Dto::SNS {

    std::string PublishResponse::ToXml() const {

        boost::property_tree::ptree root;
        root.add("PublishResponse.PublishResult.MessageId", messageId);
        root.add("PublishResponse.ResponseMetadata.RequestId", requestId);
        return Core::XmlUtils::ToXmlString(root);
    }

    std::string PublishResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "messageId", messageId);

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string PublishResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PublishResponse &r) {
        os << "PublishResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
