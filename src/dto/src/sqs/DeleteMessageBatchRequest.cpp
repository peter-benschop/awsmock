//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteMessageBatchRequest.h>

namespace AwsMock::Dto::SQS {

  void DeleteMessageBatchRequest::FromJson(const std::string &jsonString) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    const auto& rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      // Queue
      Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);

      // Entries
      Poco::JSON::Array::Ptr jsonEntriesArray = rootObject->getArray("Entries");
      for(int i = 0; i < jsonEntriesArray->size(); i++) {
        DeleteMessageBatchEntry entry;
        Poco::JSON::Object::Ptr jsonEntryObject = jsonEntriesArray->getObject(i);
        Core::JsonUtils::GetJsonValueString("Id", jsonEntryObject, entry.id);
        Core::JsonUtils::GetJsonValueString("ReceiptHandle", jsonEntryObject, entry.receiptHandle);
        deleteMessageBatchEntries.emplace_back(entry);
      }

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string DeleteMessageBatchRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchRequest &r) {
    os << "DeleteMessageBatchRequest={region='" << r.region << "', queueUrl='" + r.queueUrl + "', entries=[";
    for (const auto &entry : r.deleteMessageBatchEntries) {
      os << entry.ToString() << ", ";
    }
    os.seekp(-2, std::ostream::cur);
    os << "]}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
