//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/MessageAttribute.h>

namespace AwsMock::Dto::SQS {

  bool MessageAttribute::operator<(const AwsMock::Dto::SQS::MessageAttribute &other) const {
    return name < other.name;
  }

  std::string MessageAttribute::GetMd5Attributes(const std::vector <MessageAttribute> &attributes) {

    int length = 0;
    auto *bytes = new unsigned char[4092];

    // Sort the attributes by name
    std::vector <Dto::SQS::MessageAttribute> sortedAttributes = attributes;
    std::sort(sortedAttributes.begin(), sortedAttributes.end());

    for (const auto &a : sortedAttributes) {

      GetIntAsByteArray(a.name.length(), bytes, length);
      length += 4;
      memcpy(bytes + length, a.name.c_str(), a.name.length());
      length += a.name.length();

      std::string type = Dto::SQS::MessageAttributeDataTypeToString(a.type);
      GetIntAsByteArray(type.length(), bytes, length);
      length += 4;
      memcpy(bytes + length, type.c_str(), type.length());
      length += type.length();

      if (a.type == Dto::SQS::MessageAttributeDataType::BINARY) {
        bytes[length] = (2 & 0x000000ff);
      } else {
        bytes[length] = (1 & 0x000000ff);
      }
      length += 1;

      if (a.type == Dto::SQS::MessageAttributeDataType::BINARY) {
        int len = sizeof(a.binaryValue) / sizeof(char);
        GetIntAsByteArray(len, bytes, len);
        length += 4;
        memcpy(bytes + len, a.binaryValue, len);
        length += len;
      } else {
        GetIntAsByteArray(a.stringValue.length(), bytes, length);
        length += 4;
        memcpy(bytes + length, a.stringValue.c_str(), a.stringValue.length());
        length += a.stringValue.length();
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

  std::string MessageAttribute::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const MessageAttribute &r) {
    os << "MessageAttribute={name='" << r.name << "', stringValue='" << r.stringValue << "', binaryValue='" << r.binaryValue << "', type='" << MessageAttributeDataTypeToString(r.type) << "', transportType='" << r.transportType << "'}";
    return os;
  }
}
