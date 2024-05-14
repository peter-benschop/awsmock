//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SqsCommonRequest.h>

namespace AwsMock::Dto::SQS {

    void SqsCommonRequest::FromJson(const std::string &jsonString) {
        try {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);

            const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();
            Core::JsonUtils::GetJsonValueString("RequestId", rootObject, requestId);
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string SqsCommonRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SqsCommonRequest &r) {
        os << "SqsCommonRequest={region='" << r.region << "', requestId='" << r.requestId << "'}";
        return os;
    }

}// namespace AwsMock::Dto::SQS
