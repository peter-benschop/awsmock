//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/TagResourceResponse.h>

namespace AwsMock::Dto::SNS {

    std::string TagResourceResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "RequestId", Core::StringUtils::CreateRandomUuid());
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string TagResourceResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;
            root.add("TagResourceResponse.TagResourceResult", "");
            root.add("TagResourceResponse.ResponseMetadata.RequestId", Core::StringUtils::CreateRandomUuid());
            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string TagResourceResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TagResourceResponse &r) {
        os << "TagResourceResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
