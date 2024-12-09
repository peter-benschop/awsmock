//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/sqs/GetQueueAttributesResponse.h>

namespace AwsMock::Dto::SQS {

    std::string GetQueueAttributesResponse::ToJson() const {

        try {

            document rootDocument;
            if (!attributes.empty()) {
                document jsonAttributes;
                for (const auto &[fst, snd]: attributes) {
                    jsonAttributes.append(kvp(fst, snd));
                }
                rootDocument.append(kvp("Attributes", jsonAttributes));
            }

            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetQueueAttributesResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;
            if (attributes.empty()) {
                boost::property_tree::ptree attributeArray;
                for (const auto &[fst, snd]: attributes) {
                    boost::property_tree::ptree attElement;
                    attElement.add("Name", fst);
                    attElement.add("Value", snd);
                    attributeArray.push_back(std::make_pair("", attElement));
                }
                root.add_child("GetQueueAttributesResponse.GetQueueAttributesResult.Attributes", attributeArray);
            }

            // Metadata
            root.add("GetQueueAttributesResponse.ResponseMetadata.RequestId", requestId);
            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetQueueAttributesResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetQueueAttributesResponse &r) {
        os << "GetQueueAttributesResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
