//
// Created by vogje01 on 24/09/2023.
//

#include <awsmock/entity/sqs/MessageAttribute.h>

#include <utility>

namespace AwsMock::Database::Entity::SQS {

    //MessageAttribute::MessageAttribute(std::string name, std::string value, const MessageAttributeType &type) : attributeName(std::move(name)), attributeValue(std::move(value)), attributeType(type) {}

    view_or_value<view, value> MessageAttribute::ToDocument() const {

        view_or_value<view, value> messageAttributeDoc = make_document(
                kvp("attributeName", attributeName),
                kvp("attributeValue", attributeValue),
                kvp("systemAttribute", systemAttribute),
                kvp("attributeType", Database::Entity::SQS::MessageAttributeTypeToString(attributeType)));

        return messageAttributeDoc;
    }

    std::string MessageAttribute::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const MessageAttribute &m) {
        os << "MessageAttribute=" << bsoncxx::to_json(m.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::SQS
