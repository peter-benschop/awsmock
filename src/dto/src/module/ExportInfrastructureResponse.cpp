//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/module/ExportInfrastructureResponse.h>

namespace AwsMock::Dto::Module {

    Poco::JSON::Object ExportInfrastructureResponse::ToJsonObject() {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("includeObjects", includeObjects);
            rootJson.set("prettyPrint", prettyPrint);
            rootJson.set("infrastructure", infrastructure.ToJsonObject());

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ExportInfrastructureResponse::ToJson() {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("includeObjects", includeObjects);
            rootJson.set("prettyPrint", prettyPrint);
            rootJson.set("infrastructure", infrastructure.ToJsonObject());

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ExportInfrastructureResponse::ToString() {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, ExportInfrastructureResponse &r) {
        os << "ExportInfrastructureResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Module