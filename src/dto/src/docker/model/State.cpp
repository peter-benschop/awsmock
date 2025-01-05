//
// Created by vogje01 on 22/09/2023.
//

#include <awsmock/dto/docker/model/State.h>

namespace AwsMock::Dto::Docker {

    void State::FromDocument(const view_or_value<view, value> &document) {

        try {

            error = Core::Bson::BsonUtils::GetStringValue(document, "Error");
            errorCode = Core::Bson::BsonUtils::GetIntValue(document, "ErrorCode");
            status = Core::Bson::BsonUtils::GetStringValue(document, "Status");
            running = Core::Bson::BsonUtils::GetBoolValue(document, "Running");
            dead = Core::Bson::BsonUtils::GetBoolValue(document, "Dead");
            paused = Core::Bson::BsonUtils::GetBoolValue(document, "Paused");
            restarting = Core::Bson::BsonUtils::GetBoolValue(document, "Restarting");
            oomKilled = Core::Bson::BsonUtils::GetBoolValue(document, "OOMKilled");
            pid = Core::Bson::BsonUtils::GetIntValue(document, "Pid");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> State::ToDocument() const {

        try {
            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Error", error);
            Core::Bson::BsonUtils::SetIntValue(document, "ErrorCode", errorCode);
            Core::Bson::BsonUtils::SetStringValue(document, "Status", status);
            Core::Bson::BsonUtils::SetBoolValue(document, "Running", running);
            Core::Bson::BsonUtils::SetBoolValue(document, "Dead", dead);
            Core::Bson::BsonUtils::SetBoolValue(document, "Paused", paused);
            Core::Bson::BsonUtils::SetBoolValue(document, "Restarting", restarting);
            Core::Bson::BsonUtils::SetBoolValue(document, "OOMKilled", oomKilled);
            Core::Bson::BsonUtils::SetIntValue(document, "Pid", pid);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string State::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    void State::FromJson(const std::string &jsonString) {
        FromDocument(bsoncxx::from_json(jsonString));
    }

    std::string State::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const State &c) {
        os << "State=" << c.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Docker
