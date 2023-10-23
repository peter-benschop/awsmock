//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/DeadLetterConfig.h>

namespace AwsMock::Dto::Lambda {

    Poco::JSON::Object DeadLetterConfig::ToJsonObject() const {
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("TargetArn", targetArn);
            return rootJson;
        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

} // namespace AwsMock::Dto::lambda
