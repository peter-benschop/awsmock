//
// Created by vogje01 on 01/06/2023.
//

#include <awsmock/entity/sns/MessageAttribute.h>

namespace AwsMock::Database::Entity::SNS {

    view_or_value<view, value> MessageAttribute::ToDocument() const {

        view_or_value<view, value> messageAttributeDoc = make_document(
                kvp("attributeName", attributeName),
                kvp("attributeValue", attributeValue),
                kvp("attributeType", MessageAttributeTypeToString(attributeType)));

        return messageAttributeDoc;
    }

    std::string MessageAttribute::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string MessageAttribute::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const MessageAttribute &m) {
        os << "MessageAttribute=" << m.ToJson();
        return os;
    }

}// namespace AwsMock::Database::Entity::SNS
