
#include <awsmock/dto/sqs/DeleteMessageBatchResponse.h>

namespace AwsMock::Dto::SQS {

    std::string DeleteMessageBatchResponse::ToJson() const {

        try {

            document document;
            if (!failed.empty()) {
                array failedArray;
                for (const auto &fail: failed) {
                    failedArray.append(fail.ToDocument());
                }
                document.append(kvp("Failed", failedArray));
            }

            if (!successFull.empty()) {
                array successArray;
                for (const auto &success: successFull) {
                    successArray.append(success.ToDocument());
                }
                document.append(kvp("Successful", successArray));
            }

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteMessageBatchResponse::ToXml() const {

        try {

            boost::property_tree::ptree pt;

            // Failed
            if (failed.empty()) {
                boost::property_tree::ptree failedArray;
                for (const auto &[id, code, senderFault, message]: failed) {
                    boost::property_tree::ptree element;
                    element.put("Id", id);
                    element.put("Code", code);
                    element.put("SenderFault", senderFault);
                    element.put("Message", message);
                    failedArray.push_back(std::make_pair("", element));
                }
                pt.add_child("DeleteMessageBatchResponse.DeleteMessageBatchResult.Failed", failedArray);
            }

            // Successful
            if (successFull.empty()) {
                boost::property_tree::ptree successArray;
                for (const auto &[id]: successFull) {
                    boost::property_tree::ptree element;
                    element.put("Id", id);
                    successArray.push_back(std::make_pair("", element));
                }
                pt.add_child("DeleteMessageBatchResponse.DeleteMessageBatchResult.Successful", successArray);
            }

            // Metadata
            pt.put("DeleteMessageBatchResponse.ResponseMetadata.RequestId", requestId);
            return Core::XmlUtils::ToXmlString(pt);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    [[nodiscard]] std::string DeleteMessageBatchResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchResponse &r) {
        os << "DeleteMessageBatchResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
