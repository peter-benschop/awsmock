//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/DescribeKeyRequest.h>

namespace AwsMock::Dto::KMS {

    void DescribeKeyRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("KeyId", rootObject, keyId);

            if (rootObject->has("GrantTokens")) {
                Poco::JSON::Array::Ptr jsonTokenArray = rootObject->getArray("GrantTokens");
                for (int i = 0; i < jsonTokenArray->size(); i++) {
                    grantTokens.emplace_back(jsonTokenArray->getElement<std::string>(i));
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DescribeKeyRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("KeyId", keyId);

            Poco::JSON::Array tokenArray;
            for (const auto &token: grantTokens) {
                tokenArray.add(token);
            }
            rootJson.set("GrantTokens", tokenArray);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }


    std::string DescribeKeyRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeKeyRequest &r) {
        os << "DescribeKeyRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
