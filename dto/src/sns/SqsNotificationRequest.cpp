//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/SqsNotificationRequest.h>

namespace AwsMock::Dto::SNS {

  std::string SqsNotificationRequest::ToJson() const {
    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Type", type);
      rootJson.set("MessageId", messageId);
      rootJson.set("MessageId", topicArn);
      rootJson.set("Message", message);
      rootJson.set("Timestamp", Poco::DateTimeFormatter::format(timestamp, Poco::DateTimeFormat::ISO8601_FRAC_FORMAT));
      rootJson.set("SignatureVersion", signatureVersion);
      rootJson.set("Signature", signature);
      rootJson.set("SignatureCertURL", signingCertURL);
      rootJson.set("UnsubscribeURL", unsubscribeURL);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string SqsNotificationRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SqsNotificationRequest &r) {
    os << "SqsNotificationRequest={type='" << r.type << "', topicArn='" << r.topicArn << "', message='" << r.message << "', timestamp='" << Poco::DateTimeFormatter::format(r.timestamp, Poco::DateTimeFormat::HTTP_FORMAT) <<
       "', signatureVersion='" << r.signatureVersion << "',  signature='" << r.signature << "', signingCertURL='" << r.signingCertURL << "', unsubscribeURL='" << r.unsubscribeURL << "'}";
    return os;
  }

} // namespace AwsMock::Dto::SNS
