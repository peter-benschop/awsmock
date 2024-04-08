//
// Created by vogje01 on 12/10/23.
//

#include <awsmock/entity/sqs/RedrivePolicy.h>

namespace AwsMock::Database::Entity::SQS {

  void RedrivePolicy::FromJson(const std::string &body) {

    if (body.empty()) {
      return;
    }

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(body);
    Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {
      if (rootObject->has("deadLetterTargetArn") && rootObject->get("deadLetterTargetArn").isString()) {
        deadLetterTargetArn = rootObject->get("deadLetterTargetArn").convert<std::string>();
        maxReceiveCount = rootObject->get("maxReceiveCount").convert<int>();
      }

      // Cleanup
      rootObject->clear();
      parser.reset();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string RedrivePolicy::ToJson() const {

    if (deadLetterTargetArn.empty()) {
      return {};
    }

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("deadLetterTargetArn", deadLetterTargetArn);
      rootJson.set("maxReceiveCount", maxReceiveCount);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  void RedrivePolicy::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

    Core::JsonUtils::GetJsonValueInt("maxReceiveCount", jsonObject, maxReceiveCount);
    Core::JsonUtils::GetJsonValueString("deadLetterTargetArn", jsonObject, deadLetterTargetArn);
  }

  view_or_value<view, value> RedrivePolicy::ToDocument() const {

    view_or_value<view, value> redrivePolicyDoc = make_document(
        kvp("deadLetterTargetArn", deadLetterTargetArn),
        kvp("maxReceiveCount", maxReceiveCount));

    return redrivePolicyDoc;
  }

  void RedrivePolicy::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    deadLetterTargetArn = bsoncxx::string::to_string(mResult.value()["deadLetterTargetArn"].get_string().value);
    maxReceiveCount = mResult.value()["maxReceiveCount"].get_int32().value;
  }

  Poco::JSON::Object RedrivePolicy::ToJsonObject() const {
    Poco::JSON::Object jsonObject;
    jsonObject.set("deadLetterTargetArn", deadLetterTargetArn);
    jsonObject.set("maxReceiveCount", maxReceiveCount);
    return jsonObject;
  }

  std::string RedrivePolicy::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const RedrivePolicy &r) {
    os << "RedrivePolicy={deadLetterTargetArn='" << r.deadLetterTargetArn << "' maxReceiveCount='" << r.maxReceiveCount
       << "'}";
    return os;
  }

} // namespace AwsMock::Database::Entity::SQS
