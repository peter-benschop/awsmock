//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/MessageAttribute.h>

namespace AwsMock::Dto::SQS {

  bool MessageAttribute::operator<(const AwsMock::Dto::SQS::MessageAttribute &other) const {
    return name < other.name;
  }

  std::string MessageAttribute::GetMd5Attributes(const std::map<std::string, MessageAttribute> &attributes, bool systemAttribute) {

    int length = 0;
    auto *bytes = new unsigned char[4092];

    for (const auto &a : attributes) {

      if (a.second.systemAttribute == systemAttribute) {
        GetIntAsByteArray(a.first.length(), bytes, length);
        length += 4;
        memcpy(bytes + length, a.first.c_str(), a.first.length());
        length += a.first.length();

        std::string type = Dto::SQS::MessageAttributeDataTypeToString(a.second.type);
        GetIntAsByteArray(type.length(), bytes, length);
        length += 4;
        memcpy(bytes + length, type.c_str(), type.length());
        length += type.length();

        if (a.second.type == Dto::SQS::MessageAttributeDataType::BINARY) {
          bytes[length] = (2 & 0x000000ff);
        } else {
          bytes[length] = (1 & 0x000000ff);
        }
        length += 1;

        if (a.second.type == Dto::SQS::MessageAttributeDataType::BINARY) {
          int len = sizeof(a.second.binaryValue) / sizeof(char);
          GetIntAsByteArray(len, bytes, len);
          length += 4;
          memcpy(bytes + len, a.second.binaryValue, len);
          length += len;
        } else {
          GetIntAsByteArray(a.second.stringValue.length(), bytes, length);
          length += 4;
          memcpy(bytes + length, a.second.stringValue.c_str(), a.second.stringValue.length());
          length += a.second.stringValue.length();
        }
      }
    }

    // Calculate MD5 of byte array
    std::string output = Core::Crypto::GetMd5FromString(std::string(reinterpret_cast<const char *>(bytes), length));

    return output;
  }

  void MessageAttribute::GetIntAsByteArray(int n, unsigned char *bytes, int offset) {
    bytes[offset + 3] = n & 0x000000ff;
    bytes[offset + 2] = (n & 0x0000ff00) >> 8;
    bytes[offset + 1] = (n & 0x00ff0000) >> 16;
    bytes[offset] = (n & 0xff000000) >> 24;
  }

  void MessageAttribute::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {


    Core::JsonUtils::GetJsonValueString("Name", jsonObject, name);
    Core::JsonUtils::GetJsonValueString("StringValue", jsonObject, stringValue);
    if(!stringValue.empty()) {
      type = MessageAttributeDataType::STRING;
    }
    Core::JsonUtils::GetJsonValueLong("NumberValue", jsonObject, numberValue);
    if(numberValue > 0) {
      type = MessageAttributeDataType::NUMBER;
    }
  }

  std::string MessageAttribute::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const MessageAttribute &r) {
    os << "MessageAttribute={name='" << r.name << "', type='" << MessageAttributeDataTypeToString(r.type) << "', transportType='" << r.transportType << "', stringValue='" << r.stringValue << "', numberValue=" << r.numberValue;
    if(r.binaryValue != nullptr) {
      os << " binaryValue='" << r.binaryValue;
    }
    os << "'}";
    return os;
  }
}
