//
// Created by vogje01 on 12/10/23.
//

#include <awsmock/entity/sqs/RedrivePolicy.h>

namespace AwsMock::Database::Entity::SQS {

    std::string RedrivePolicy::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> RedrivePolicy::ToDocument() const {

        view_or_value<view, value> redrivePolicyDoc = make_document(
                kvp("deadLetterTargetArn", deadLetterTargetArn),
                kvp("maxReceiveCount", maxReceiveCount));

        return redrivePolicyDoc;
    }

    void RedrivePolicy::FromDocument(const std::optional<view> &mResult) {

        deadLetterTargetArn = bsoncxx::string::to_string(mResult.value()["deadLetterTargetArn"].get_string().value);
        maxReceiveCount = mResult.value()["maxReceiveCount"].get_int32().value;
    }

    std::string RedrivePolicy::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const RedrivePolicy &r) {
        os << "RedrivePolicy=" << to_json(r.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::SQS
