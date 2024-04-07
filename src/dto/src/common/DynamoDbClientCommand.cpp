//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/DynamoDbClientCommand.h>

namespace AwsMock::Dto::Common {

  void DynamoDbClientCommand::FromRequest(const HttpMethod &method, Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user) {

    // Basic values
    this->region = region;
    this->user = user;
    this->method = method;

    // Command
    std::string action = request.get("X-Amz-Target");

    switch (method) {
      case HttpMethod::GET:
      case HttpMethod::PUT:
      case HttpMethod::DELETE:break;
      case HttpMethod::POST:
        if (Core::StringUtils::ContainsIgnoreCase(action, "CreateTable")) {
          command = DynamoDbCommandType::CREATE_TABLE;
        } else if (Core::StringUtils::ContainsIgnoreCase(action, "ListTables")) {
          command = DynamoDbCommandType::LIST_TABLES;
        } else if (Core::StringUtils::ContainsIgnoreCase(action, "DescribeTable")) {
          command = DynamoDbCommandType::DESCRIBE_TABLE;
        } else if (Core::StringUtils::ContainsIgnoreCase(action, "DeleteTable")) {
          command = DynamoDbCommandType::DELETE_TABLE;
        } else if (Core::StringUtils::ContainsIgnoreCase(action, "PutItem")) {
          command = DynamoDbCommandType::PUT_ITEM;
        } else if (Core::StringUtils::ContainsIgnoreCase(action, "GetItem")) {
          command = DynamoDbCommandType::GET_ITEM;
        } else if (Core::StringUtils::ContainsIgnoreCase(action, "Query")) {
          command = DynamoDbCommandType::QUERY;
        } else if (Core::StringUtils::ContainsIgnoreCase(action, "Scan")) {
          command = DynamoDbCommandType::SCAN;
        }
        break;
      case HttpMethod::UNKNOWN: {
        break;
      }
    }
  }

  /* void DynamoDbClientCommand::GetCommandFromUserAgent(const HttpMethod &httpMethod, const UserAgent &userAgent) {
     if (userAgent.clientCommand == "mb") {
       command = S3CommandType::CREATE_BUCKET;
     } else if (userAgent.clientCommand == "ls") {
       if (bucket.empty() && key.empty()) {
         command = S3CommandType::LIST_BUCKETS;
       } else if (!bucket.empty()) {
         command = S3CommandType::LIST_OBJECTS;
       }
     } else if (userAgent.clientCommand == "cp") {
       if (httpMethod == HttpMethod::PUT) {
         if (multipartRequest) {
           command = S3CommandType::UPLOAD_PART;
         } else {
           command = S3CommandType::PUT_OBJECT;
         }
       } else if (httpMethod == HttpMethod::GET) {
         command = S3CommandType::GET_OBJECT;
       } else if (httpMethod == HttpMethod::POST) {
         if (multipartRequest && uploadId.empty()) {
           command = S3CommandType::CREATE_MULTIPART_UPLOAD;
         } else {
           command = S3CommandType::COMPLETE_MULTIPART_UPLOAD;
         }
       }
     } else if (userAgent.clientCommand == "mv") {
       command = S3CommandType::MOVE_OBJECT;
     } else if (userAgent.clientCommand == "rb") {
       command = S3CommandType::DELETE_BUCKET;
     } else if (userAgent.clientCommand == "rm") {
       command = S3CommandType::DELETE_OBJECT;
     } else if (userAgent.clientModule == "command/s3api" && userAgent.clientCommand == "create-multipart-upload") {
       command = S3CommandType::CREATE_MULTIPART_UPLOAD;
     } else if (userAgent.clientModule == "command/s3api" && userAgent.clientCommand == "upload-part") {
       command = S3CommandType::UPLOAD_PART;
     } else if (userAgent.clientModule == "command/s3api" && userAgent.clientCommand == "complete-multipart-upload") {
       command = S3CommandType::COMPLETE_MULTIPART_UPLOAD;
     }
   }*/

  std::string DynamoDbClientCommand::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DynamoDbClientCommand &r) {
    os << "DynamoDbClientCommand={method='" << HttpMethodToString(r.method) << ", region='" << r.region << "', user='" << r.user << "', command='" << DynamoDbCommandTypeToString(r.command) << "}";
    return os;
  }
}
