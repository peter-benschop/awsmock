//
// Created by vogje01 on 11/26/23.
//

#include <awsmock/dto/common/SQSClientCommand.h>

namespace AwsMock::Dto::Common {

  void SQSClientCommand::FromRequest(const HttpMethod &method, Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user) {

    Dto::Common::UserAgent userAgent;
    userAgent.FromRequest(request, "sqs");

    // Basic values
    this->region = region;
    this->user = user;
    this->method = method;

    // Core values
    //bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
    //key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);

    // Qualifiers
    std::string url = request.getURI();

    if (!userAgent.clientCommand.empty()) {

      GetCommandFromUserAgent(method, userAgent);

    } else {

      switch (method) {
        case HttpMethod::GET:
          /*if (bucket.empty() && key.empty()) {
            command = SQSCommandType::LIST_BUCKETS;
          } else if (!bucket.empty() && key.empty()) {
            command = S3CommandType::LIST_OBJECTS;
          } else {
            command = S3CommandType::GET_OBJECT;
          }*/
          break;
        case HttpMethod::PUT:
          /*if (!bucket.empty() && key.empty()) {
            command = S3CommandType::CREATE_BUCKET;
          } else if (!bucket.empty() && !key.empty()) {
            command = S3CommandType::PUT_OBJECT;
          }*/
          break;
        case HttpMethod::DELETE:
          /*if (!bucket.empty() && key.empty()) {
            command = S3CommandType::DELETE_BUCKET;
          } else if (!bucket.empty() && !key.empty()) {
            command = S3CommandType::DELETE_OBJECT;
          }*/
          break;
        case HttpMethod::POST:
          /*if (!bucket.empty()) {
            command = S3CommandType::DELETE_OBJECTS;
          }*/
          break;
        case HttpMethod::UNKNOWN: {
          break;
        }
      }
    }
  }

  void SQSClientCommand::GetCommandFromUserAgent(const HttpMethod &httpMethod, const UserAgent &userAgent) {
    /*if (userAgent.clientCommand == "mb") {
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
    }*/
  }

  std::string SQSClientCommand::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SQSClientCommand &r) {
    os << "SQSClientCommand={method='" << HttpMethodToString(r.method) << ", region='" << r.region << "', user='" << r.user << "', command='" << SqsCommandTypeToString(r.command) << "}";
    return os;
  }
}
