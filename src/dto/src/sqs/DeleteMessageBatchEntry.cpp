//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteMessageBatchEntry.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteMessageBatchEntry::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Id", id);
            rootJson.set("ReceiptHandle", receiptHandle);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    Poco::JSON::Object DeleteMessageBatchEntry::ToJsonObject() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Id", id);
            rootJson.set("ReceiptHandle", receiptHandle);
            return rootJson;

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    std::string DeleteMessageBatchEntry::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchEntry &d) {
        os << "DeleteMessageBatchEntry=" << d.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
