//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/ValidationData.h>

namespace AwsMock::Dto::Cognito {

    std::string ValidationData::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void ValidationData::FromDocument(const view_or_value<view, value> &document) {

        // TODO: fix me
        /*try {

            Core::JsonUtils::GetJsonValueString("Name", jsonObject, name);
            Core::JsonUtils::GetJsonValueString("Value", jsonObject, value);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
    }

    view_or_value<view, value> ValidationData::ToDocument() const {

        // TODO: fix me
        /*try {
            Poco::JSON::Object rootJson;
            rootJson.set("Name", name);
            rootJson.set("Value", value);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    std::string ValidationData::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ValidationData &o) {
        os << "ValidationData=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
