//
// Created by vogje01 on 03/10/2023.
//

#include "awsmock/dto/sns/model/Subscription.h"

namespace AwsMock::Dto::SNS {

    std::string Subscription::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object Subscription::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("id", id);
            rootJson.set("region", region);
            rootJson.set("topicArn", topicArn);
            rootJson.set("protocol", protocol);
            rootJson.set("subscriptionArn", subscriptionArn);
            rootJson.set("endpoint", endpoint);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Subscription::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Subscription &r) {
        os << "Subscription={region='" << r.region << "', topicArn='" << r.topicArn + "', owner='" << r.owner << "', protocol='" << r.protocol << "', endpoint='"
           << r.endpoint << "'}";
        return os;
    }
}// namespace AwsMock::Dto::SNS
