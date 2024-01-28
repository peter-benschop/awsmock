//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/MessageAttribute.h>

namespace AwsMock::Dto::SQS {

  bool MessageAttribute::operator<(const AwsMock::Dto::SQS::MessageAttribute &other) const {
    return name < other.name;
  }

  std::string MessageAttribute::GetMd5UserAttributes(const std::map<std::string, MessageAttribute> &attributes) {

    EVP_MD_CTX *context = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_md5();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    auto *bytes = new unsigned char[1];

    EVP_DigestInit_ex(context, md, nullptr);
    for (const auto &a : attributes) {

      if (!a.second.systemAttribute) {

        // Encoded name
        updateLengthAndBytes(context, a.first);

        // Encoded data type
        updateLengthAndBytes(context, Dto::SQS::MessageAttributeDataTypeToString(a.second.type));

        // Encoded value
        if (!a.second.stringValue.empty()) {
          bytes[0] = 1;
          EVP_DigestUpdate(context, bytes, 1);
          updateLengthAndBytes(context, a.second.stringValue);
        }
      }
    }
    EVP_DigestFinal(context, md_value, &md_len);
    EVP_MD_CTX_free(context);

    std::string output;
    output.resize(md_len * 2);
    for (unsigned int i = 0; i < md_len; ++i) {
      std::sprintf(&output[i * 2], "%02x", md_value[i]);
    }

    return output;
  }

  std::string MessageAttribute::GetMd5SystemAttributes(const std::map<std::string, MessageAttribute> &attributes) {

    EVP_MD_CTX *context = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_md5();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    std::string output;

    EVP_DigestInit_ex(context, md, nullptr);
    for (const auto &a : attributes) {

      if (a.second.systemAttribute) {

        // Encoded name
        updateLengthAndBytes(context, a.first);

        // Encoded data type
        updateLengthAndBytes(context, Dto::SQS::MessageAttributeDataTypeToString(a.second.type));

        // Encoded value
        if (!a.second.stringValue.empty()) {
          EVP_DigestUpdate(context, reinterpret_cast<const void *>(0x01), 1);
          updateLengthAndBytes(context, a.second.stringValue);
        }
      }
    }
    EVP_DigestFinal_ex(context, md_value, &md_len);
    EVP_MD_CTX_free(context);

    output.resize(md_len * 2);
    for (unsigned int i = 0; i < md_len; ++i) {
      std::sprintf(&output[i * 2], "%02x", md_value[i]);
    }
    return output;
  }

  void MessageAttribute::GetIntAsByteArray(size_t n, unsigned char *bytes) {
    bytes[3] = n & 0x000000ff;
    bytes[2] = (n & 0x0000ff00) >> 8;
    bytes[1] = (n & 0x00ff0000) >> 16;
    bytes[0] = (n & 0xff000000) >> 24;
  }

  void MessageAttribute::updateLengthAndBytes(EVP_MD_CTX *context, const std::string &str) {
    auto* bytes = static_cast<unsigned char *>(malloc(4));
    GetIntAsByteArray(str.length(), bytes);
    EVP_DigestUpdate(context, bytes, 4);
    EVP_DigestUpdate(context, str.c_str(), str.length());
    free(bytes);
  }

  void MessageAttribute::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

    Core::JsonUtils::GetJsonValueString("Name", jsonObject, name);
    Core::JsonUtils::GetJsonValueString("StringValue", jsonObject, stringValue);
    if (!stringValue.empty()) {
      type = MessageAttributeDataType::STRING;
    }
    Core::JsonUtils::GetJsonValueLong("NumberValue", jsonObject, numberValue);
    if (numberValue > 0) {
      type = MessageAttributeDataType::NUMBER;
    }
  }

  std::string MessageAttribute::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const MessageAttribute &r) {
    os << "MessageAttribute={name='" << r.name << "', type='" << MessageAttributeDataTypeToString(r.type) << "', stringValue='" << r.stringValue << "', numberValue=" << r.numberValue;
    if (r.binaryValue != nullptr) {
      os << ", binaryValue='" << r.binaryValue << "'";
    }
    os << "}";
    return os;
  }
}
