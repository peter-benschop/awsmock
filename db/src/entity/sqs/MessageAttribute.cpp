//
// Created by vogje01 on 24/09/2023.
//

#include <awsmock/entity/sqs/MessageAttribute.h>

namespace AwsMock::Database::Entity::SQS {

    view_or_value<view, value> MessageAttribute::ToDocument() const {

        view_or_value<view, value> messageAttributeDoc = make_document(
            kvp("name", attributeName),
            kvp("value", attributeValue));

        return messageAttributeDoc;
    }

    std::string MessageAttribute::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const MessageAttribute &m) {
        os << "MessageAttribute={name='" + m.attributeValue + "'value='" + m.attributeValue + "'}";
        return os;
    }

} // namespace AwsMock::Database::Entity::S3
