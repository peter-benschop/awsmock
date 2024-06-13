//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/InitiateAuthRequest.h>

namespace AwsMock::Dto::Cognito {

    void InitiateAuthRequest::FromJson(const std::string &payload) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(payload);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("ClientId", rootObject, clientId);

            // Auth flow
            std::string tmpAuthFlow;
            Core::JsonUtils::GetJsonValueString("AuthFlow", rootObject, tmpAuthFlow);
            if (!tmpAuthFlow.empty()) {
                AuthFlowTypeFromString(tmpAuthFlow);
            }

            // Auth parameter
            if (rootObject->has("AuthParameter")) {
                Poco::JSON::Object::Ptr authParameterObject = rootObject->getObject("AuthParameter");
                for (int i = 0; i < authParameterObject->getNames().size(); i++) {
                    std::string key = authParameterObject->getNames()[i];
                    std::string value = authParameterObject->get(key);
                    authParameters[key] = value;
                }
            }

            // Client metadata
            if (rootObject->has("ClientMetadata")) {
                Poco::JSON::Object::Ptr clientMetadataObject = rootObject->getObject("ClientMetadata");
                for (int i = 0; i < clientMetadataObject->getNames().size(); i++) {
                    std::string key = clientMetadataObject->getNames()[i];
                    std::string value = clientMetadataObject->get(key);
                    clientMetaData[key] = value;
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string InitiateAuthRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("ClientId", clientId);
            rootJson.set("AuthFlow", AuthFlowTypeToString(authFlow));

            // Auth parameters
            Poco::JSON::Object authParameterObject;
            for (const auto &authParameter: authParameters) {
                authParameterObject.set(authParameter.first, authParameter.second);
            }
            rootJson.set("AuthParameter", authParameterObject);

            // Client metadata
            Poco::JSON::Object clientMetadataObject;
            for (const auto &clientMeta: clientMetaData) {
                clientMetadataObject.set(clientMeta.first, clientMeta.second);
            }
            rootJson.set("ClientMetadata", clientMetadataObject);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string InitiateAuthRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const InitiateAuthRequest &r) {
        os << "InitiateAuthRequest=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito