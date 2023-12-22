//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/Infrastructure.h>

namespace AwsMock::Dto::Common {

  std::string Infrastructure::ToJson(bool prettyPrint) {

    try {

      Poco::JSON::Object rootJson;
      Poco::JSON::Object infrastructureJson;

      // S3 Bucket array
      if (!s3Buckets.empty()) {
        Poco::JSON::Array jsonBucketArray;
        for (const auto &bucket : s3Buckets) {
          jsonBucketArray.add(bucket.ToJsonObject());
        }
        infrastructureJson.set("s3-buckets", jsonBucketArray);
      }

      // S3 object array
      if (!s3Objects.empty()) {
        Poco::JSON::Array jsonObjectArray;
        for (const auto &object : s3Objects) {
          jsonObjectArray.add(object.ToJsonObject());
        }
        infrastructureJson.set("s3-objects", jsonObjectArray);
      }

      // SQS queue array
      if (!sqsQueues.empty()) {
        Poco::JSON::Array jsonQueueArray;
        for (const auto &queue : sqsQueues) {
          jsonQueueArray.add(queue.ToJsonObject());
        }
        infrastructureJson.set("sqs-queues", jsonQueueArray);
      }

      // SQS message array
      if (!sqsMessages.empty()) {
        Poco::JSON::Array jsonSqsMessageArray;
        for (const auto &message : sqsMessages) {
          jsonSqsMessageArray.add(message.ToJsonObject());
        }
        infrastructureJson.set("sqs-messages", jsonSqsMessageArray);
      }

      // SNS topic array
      if (!snsTopics.empty()) {
        Poco::JSON::Array jsonTopicArray;
        for (const auto &topic : snsTopics) {
          jsonTopicArray.add(topic.ToJsonObject());
        }
        infrastructureJson.set("sns-topics", jsonTopicArray);
      }

      // SNS message array
      if (!snsMessages.empty()) {
        Poco::JSON::Array jsonSnsMessageArray;
        for (const auto &message : snsMessages) {
          jsonSnsMessageArray.add(message.ToJsonObject());
        }
        infrastructureJson.set("sns-messages", jsonSnsMessageArray);
      }

      // Lambda functions
      if (!lambdas.empty()) {
        Poco::JSON::Array jsonLambdaArray;
        for (const auto &lambda : lambdas) {
          jsonLambdaArray.add(lambda.ToJsonObject());
        }
        infrastructureJson.set("lambda-functions", jsonLambdaArray);
      }

      // Transfer server
      if (!transferServers.empty()) {
        Poco::JSON::Array jsonTransferArray;
        for (const auto &transfer : transferServers) {
          jsonTransferArray.add(transfer.ToJsonObject());
        }
        infrastructureJson.set("transfer-servers", jsonTransferArray);
      }

      // Cognito user pools
      if (!cognitoUserPools.empty()) {
        Poco::JSON::Array jsonCognitoUserPoolArray;
        for (const auto &userPool : cognitoUserPools) {
          jsonCognitoUserPoolArray.add(userPool.ToJsonObject());
        }
        infrastructureJson.set("cognito-user-pools", jsonCognitoUserPoolArray);
      }

      // Cognito users
      if (!cognitoUsers.empty()) {
        Poco::JSON::Array jsonCognitoUserArray;
        for (const auto &user : cognitoUsers) {
          jsonCognitoUserArray.add(user.ToJsonObject());
        }
        infrastructureJson.set("cognito-users", jsonCognitoUserArray);
      }

      // DynamoDb tables
      if (!dynamoDbTables.empty()) {
        Poco::JSON::Array jsonDynamoDbTableArray;
        for (const auto &table : dynamoDbTables) {
          jsonDynamoDbTableArray.add(table.ToJsonObject());
        }
        infrastructureJson.set("dynamodb-tables", jsonDynamoDbTableArray);
      }

      // DynamoDb items
      if (!dynamoDbItems.empty()) {
        Poco::JSON::Array jsonDynamoDbItemArray;
        for (const auto &item : dynamoDbItems) {
          jsonDynamoDbItemArray.add(item.ToJsonObject());
        }
        infrastructureJson.set("dynamodb-items", jsonDynamoDbItemArray);
      }

      // Add infrastructure JSON to root JSON
      rootJson.set("infrastructure", infrastructureJson);

      int indent = 0;
      std::ostringstream os;
      if (prettyPrint) {
        indent = JSON_DEFAULT_INDENT;
      }
      rootJson.stringify(os, indent);
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

      Poco::JSON::Array::Ptr sqsQueueArray = infrastructureObject->getArray("sqs-queues");
      for (int i = 0; i < sqsQueueArray->size(); i++) {
        Database::Entity::SQS::Queue sqsQueueObject;
        sqsQueueObject.FromJsonObject(sqsQueueArray->getObject(i));
        sqsQueues.emplace_back(sqsQueueObject);
      }

      Poco::JSON::Array::Ptr sqsMessageArray = infrastructureObject->getArray("sqs-messages");
      for (int i = 0; i < sqsMessageArray->size(); i++) {
        Database::Entity::SQS::Message sqsMessageObject;
        sqsMessageObject.FromJsonObject(sqsMessageArray->getObject(i));
        sqsMessages.emplace_back(sqsMessageObject);
      }

      Poco::JSON::Array::Ptr cognitoUserPoolArray = infrastructureObject->getArray("cognito-user-pools");
      for (int i = 0; i < cognitoUserPoolArray->size(); i++) {
        Database::Entity::Cognito::UserPool cognitoUserPoolObject;
        cognitoUserPoolObject.FromJsonObject(cognitoUserPoolArray->getObject(i));
        cognitoUserPools.emplace_back(cognitoUserPoolObject);
      }

      Poco::JSON::Array::Ptr cognitoUserArray = infrastructureObject->getArray("cognito-users");
      for (int i = 0; i < cognitoUserArray->size(); i++) {
        Database::Entity::Cognito::User cognitoUserObject;
        cognitoUserObject.FromJsonObject(cognitoUserArray->getObject(i));
        cognitoUsers.emplace_back(cognitoUserObject);
      }

      Poco::JSON::Array::Ptr dynamoDbTableArray = infrastructureObject->getArray("dynamodb-tables");
      for (int i = 0; i < dynamoDbTableArray->size(); i++) {
        Database::Entity::DynamoDb::Table dynamoDbTableObject;
        dynamoDbTableObject.FromJsonObject(dynamoDbTableArray->getObject(i));
        dynamoDbTables.emplace_back(dynamoDbTableObject);
      }

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }

  }
}