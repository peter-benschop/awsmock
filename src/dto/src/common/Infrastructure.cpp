//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/Infrastructure.h>

namespace AwsMock::Dto::Common {

  std::string Infrastructure::ToJson() {

    try {

      // S3 Bucket array
      Poco::JSON::Array jsonBucketArray;
      for (const auto &bucket : s3Buckets) {
        jsonBucketArray.add(bucket.ToJsonObject());
      }

      // S3 object array
      Poco::JSON::Array jsonObjectArray;
      for (const auto &object : s3Objects) {
        jsonObjectArray.add(object.ToJsonObject());
      }

      // SQS queue array
      Poco::JSON::Array jsonQueueArray;
      for (const auto &queue : sqsQueues) {
        jsonQueueArray.add(queue.ToJsonObject());
      }

      // SQS message array
      Poco::JSON::Array jsonSqsMessageArray;
      for (const auto &message : sqsMessages) {
        jsonSqsMessageArray.add(message.ToJsonObject());
      }

      // SNS topic array
      Poco::JSON::Array jsonTopicArray;
      for (const auto &topic : snsTopics) {
        jsonTopicArray.add(topic.ToJsonObject());
      }

      // SNS message array
      Poco::JSON::Array jsonSnsMessageArray;
      for (const auto &message : snsMessages) {
        jsonSnsMessageArray.add(message.ToJsonObject());
      }

      // Lambda functions
      Poco::JSON::Array jsonLambdaArray;
      for (const auto &lambda : lambdas) {
        jsonLambdaArray.add(lambda.ToJsonObject());
      }

      // Transfer server
      Poco::JSON::Array jsonTransferArray;
      for (const auto &transfer : transferServers) {
        jsonTransferArray.add(transfer.ToJsonObject());
      }

      // Cognito user pools
      Poco::JSON::Array jsonCognitoUserPoolArray;
      for (const auto &userPool : cognitoUserPools) {
        jsonCognitoUserPoolArray.add(userPool.ToJsonObject());
      }

      // Cognito users
      Poco::JSON::Array jsonCognitoUserArray;
      for (const auto &user : cognitoUsers) {
        jsonCognitoUserArray.add(user.ToJsonObject());
      }

      Poco::JSON::Object infrastructureJson;
      if (!jsonBucketArray.empty()) {
        infrastructureJson.set("s3-buckets", jsonBucketArray);
      }
      if (!jsonObjectArray.empty()) {
        infrastructureJson.set("s3-objects", jsonObjectArray);
      }
      if (!jsonQueueArray.empty()) {
        infrastructureJson.set("sqs-queues", jsonQueueArray);
      }
      if (!jsonSqsMessageArray.empty()) {
        infrastructureJson.set("sqs-messages", jsonSqsMessageArray);
      }
      if (!jsonTopicArray.empty()) {
        infrastructureJson.set("sns-topics", jsonTopicArray);
      }
      if (!jsonSnsMessageArray.empty()) {
        infrastructureJson.set("sns-messages", jsonSnsMessageArray);
      }
      if (!jsonLambdaArray.empty()) {
        infrastructureJson.set("lambda-functions", jsonLambdaArray);
      }
      if (!jsonTransferArray.empty()) {
        infrastructureJson.set("transfer-servers", jsonTransferArray);
      }
      if (!jsonCognitoUserPoolArray.empty()) {
        infrastructureJson.set("cognito-user-pools", jsonCognitoUserPoolArray);
      }
      if (!jsonCognitoUserArray.empty()) {
        infrastructureJson.set("cognito-users", jsonCognitoUserArray);
      }

      Poco::JSON::Object rootJson;
      rootJson.set("infrastructure", infrastructureJson);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  void Infrastructure::FromJson(const std::string &jsonString) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();
    const auto &infrastructureObject = rootObject->getObject("infrastructure");

    try {

      Poco::JSON::Array::Ptr s3BucketArray = infrastructureObject->getArray("s3-buckets");
      for (int i = 0; i < s3BucketArray->size(); i++) {
        Database::Entity::S3::Bucket bucket;
        bucket.FromJsonObject(s3BucketArray->getObject(i));
        s3Buckets.emplace_back(bucket);
      }

      Poco::JSON::Array::Ptr s3ObjectArray = infrastructureObject->getArray("s3-objects");
      for (int i = 0; i < s3ObjectArray->size(); i++) {
        Database::Entity::S3::Object s3Object;
        s3Object.FromJsonObject(s3ObjectArray->getObject(i));
        s3Objects.emplace_back(s3Object);
      }

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }

  }
}