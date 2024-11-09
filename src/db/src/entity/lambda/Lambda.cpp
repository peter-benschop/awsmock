//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/Lambda.h>

namespace AwsMock::Database::Entity::Lambda {

    bool Lambda::HasEventSource(const std::string &eventSourceArn) const {
        return find_if(eventSources.begin(), eventSources.end(), [eventSourceArn](const EventSourceMapping &e) {
                   return e.eventSourceArn == eventSourceArn;
               }) != eventSources.end();
    }

    bool Lambda::HasTag(const std::string &key) const {
        return find_if(tags.begin(), tags.end(), [key](const std::pair<std::string, std::string> &t) {
                   return t.first == key;
               }) != tags.end();
    }

    std::string Lambda::GetTagValue(const std::string &key) const {
        auto it = find_if(tags.begin(), tags.end(), [key](const std::pair<std::string, std::string> &t) {
            return t.first == key;
        });
        return it->second;
    }

    Instance Lambda::GetInstance(const std::string &instanceId) {
        auto it = std::ranges::find(instances, instanceId, &Instance::id);
        if (it != instances.end()) {
            return *it;
        }
        log_error << "Lambda instance not found, id: " << instanceId;
        return {};
    }

    void Lambda::RemoveInstance(const AwsMock::Database::Entity::Lambda::Instance &instance) {
        std::string id = instance.id;
        instances.erase(std::remove_if(instances.begin(), instances.end(), [&id](const Instance &instance) { return id == instance.id; }), instances.end());
    }

    view_or_value<view, value> Lambda::ToDocument() const {

        // Convert instances
        auto instancesDoc = bsoncxx::builder::basic::array{};
        for (const auto &instance: instances) {
            instancesDoc.append(instance.ToDocument());
        }

        // Convert environment to document
        auto variablesDoc = bsoncxx::builder::basic::array{};
        for (const auto &variables: environment.variables) {
            variablesDoc.append(make_document(kvp(variables.first, variables.second)));
        }
        view_or_value<view, value> varDoc = make_document(kvp("variables", variablesDoc));

        // Convert tags to document
        auto tagsDoc = bsoncxx::builder::basic::document{};
        for (const auto &t: tags) {
            tagsDoc.append(kvp(t.first, t.second));
        }

        // Convert event source mappings
        auto eventSourcesDoc = bsoncxx::builder::basic::array{};
        for (const auto &e: eventSources) {
            eventSourcesDoc.append(e.ToDocument());
        }

        view_or_value<view, value> ephemeralStorageDoc = make_document(kvp("size", static_cast<bsoncxx::types::b_int64>(ephemeralStorage.size)));

        bsoncxx::builder::basic::document lambdaDoc;
        lambdaDoc.append(
                kvp("region", region),
                kvp("user", user),
                kvp("function", function),
                kvp("runtime", runtime),
                kvp("role", role),
                kvp("handler", handler),
                kvp("memorySize", static_cast<bsoncxx::types::b_int64>(memorySize)),
                kvp("ephemeralStorage", ephemeralStorageDoc),
                kvp("codeSize", static_cast<bsoncxx::types::b_int64>(codeSize)),
                kvp("imageId", imageId),
                kvp("containerId", containerId),
                kvp("tags", tagsDoc),
                kvp("arn", arn),
                kvp("timeout", timeout),
                kvp("concurrency", concurrency),
                kvp("codeSha256", codeSha256),
                kvp("environment", varDoc),
                kvp("code", code.ToDocument()),
                kvp("state", LambdaStateToString(state)),
                kvp("stateReason", stateReason),
                kvp("stateReasonCode", LambdaStateReasonCodeToString(stateReasonCode)),
                kvp("instances", instancesDoc),
                kvp("invocations", invocations),
                kvp("averageRuntime", averageRuntime),
                kvp("eventSources", eventSourcesDoc),
                kvp("lastStarted", bsoncxx::types::b_date(lastStarted)),
                kvp("lastInvocation", bsoncxx::types::b_date(lastInvocation)),
                kvp("created", bsoncxx::types::b_date(created)),
                kvp("modified", bsoncxx::types::b_date(modified)));
        return lambdaDoc.extract();
    }

    void Lambda::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
        user = bsoncxx::string::to_string(mResult.value()["user"].get_string().value);
        function = bsoncxx::string::to_string(mResult.value()["function"].get_string().value);
        runtime = bsoncxx::string::to_string(mResult.value()["runtime"].get_string().value);
        role = bsoncxx::string::to_string(mResult.value()["role"].get_string().value);
        handler = bsoncxx::string::to_string(mResult.value()["handler"].get_string().value);
        memorySize = mResult.value()["memorySize"].get_int64().value;
        ephemeralStorage.FromDocument(mResult.value()["ephemeralStorage"].get_document().value);
        codeSize = mResult.value()["codeSize"].get_int64().value;
        imageId = bsoncxx::string::to_string(mResult.value()["imageId"].get_string().value);
        containerId = bsoncxx::string::to_string(mResult.value()["containerId"].get_string().value);
        arn = bsoncxx::string::to_string(mResult.value()["arn"].get_string().value);
        codeSha256 = bsoncxx::string::to_string(mResult.value()["codeSha256"].get_string().value);
        timeout = mResult.value()["timeout"].get_int32().value;
        concurrency = mResult.value()["concurrency"].get_int32().value;
        environment.FromDocument(mResult.value()["environment"].get_document().value);
        state = LambdaStateFromString(bsoncxx::string::to_string(mResult.value()["state"].get_string().value));
        stateReason = bsoncxx::string::to_string(mResult.value()["stateReason"].get_string().value);
        stateReasonCode = LambdaStateReasonCodeFromString(bsoncxx::string::to_string(mResult.value()["stateReasonCode"].get_string().value));
        lastStarted = bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date().value);
        lastInvocation = bsoncxx::types::b_date(mResult.value()["lastInvocation"].get_date().value);
        invocations = mResult.value()["invocations"].get_int64().value;
        averageRuntime = mResult.value()["averageRuntime"].get_int64().value;
        created = bsoncxx::types::b_date(mResult.value()["created"].get_date().value);
        modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date().value);

        // Get tags
        if (mResult.value().find("tags") != mResult.value().end()) {
            bsoncxx::document::view tagsView = mResult.value()["tags"].get_document().value;
            for (const bsoncxx::document::element &tagElement: tagsView) {
                std::string key = bsoncxx::string::to_string(tagElement.key());
                std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
                tags.emplace(key, value);
            }
        }

        // Get code
        if (mResult.value().find("code") != mResult.value().end()) {
            code.FromDocument(mResult.value()["code"].get_document().value);
        }

        // Get instances
        if (mResult.value().find("instances") != mResult.value().end()) {
            bsoncxx::document::view instancesView = mResult.value()["instances"].get_array().value;
            for (const bsoncxx::document::element &instanceElement: instancesView) {
                Instance instance;
                instance.FromDocument(instanceElement.get_document().view());
                instances.emplace_back(instance);
            }
        }

        // Get event sources
        if (mResult.value().find("eventSources") != mResult.value().end()) {
            bsoncxx::document::view eventSourcesView = mResult.value()["eventSources"].get_array().value;
            for (const bsoncxx::document::element &eventSourceElement: eventSourcesView) {
                EventSourceMapping eventSourceMapping;
                eventSourceMapping.FromDocument(eventSourceElement.get_document().view());
                eventSources.emplace_back(eventSourceMapping);
            }
        }
    }

    Poco::JSON::Object Lambda::ToJsonObject() const {

        try {

            Poco::JSON::Object jsonObject;
            jsonObject.set("region", region);
            jsonObject.set("user", user);
            jsonObject.set("function", function);
            jsonObject.set("runtime", runtime);
            jsonObject.set("role", role);
            jsonObject.set("handler", handler);
            jsonObject.set("memorySize", memorySize);
            jsonObject.set("ephemeralStorage", ephemeralStorage.ToJsonObject());
            jsonObject.set("codeSize", codeSize);
            jsonObject.set("imageId", imageId);
            jsonObject.set("containerId", containerId);
            jsonObject.set("arn", arn);
            jsonObject.set("codeSha256", codeSha256);
            jsonObject.set("timeout", timeout);
            jsonObject.set("concurrency", concurrency);
            jsonObject.set("environment", environment.ToJsonObject());
            jsonObject.set("code", code.ToJsonObject());
            jsonObject.set("state", LambdaStateToString(state));
            jsonObject.set("stateReason", stateReason);
            jsonObject.set("lastStarted", Core::DateTimeUtils::ToISO8601(lastStarted));
            jsonObject.set("lastInvocation", Core::DateTimeUtils::ToISO8601(lastInvocation));

            // Tags
            if (!tags.empty()) {
                Poco::JSON::Array jsonTagArray;
                for (const auto &tag: tags) {
                    Poco::JSON::Object jsonTagObject;
                    jsonTagObject.set(tag.first, tag.second);
                    jsonTagArray.add(jsonTagObject);
                }
                jsonObject.set("tags", jsonTagArray);
            }

            return jsonObject;


        } catch (Poco::Exception &e) {
            log_error << "JSON Exception" << e.message();
            throw Core::JsonException(e.message());
        }
    }

    void Lambda::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
            Core::JsonUtils::GetJsonValueString("user", jsonObject, user);
            Core::JsonUtils::GetJsonValueString("function", jsonObject, function);
            Core::JsonUtils::GetJsonValueString("runtime", jsonObject, runtime);
            Core::JsonUtils::GetJsonValueString("role", jsonObject, role);
            Core::JsonUtils::GetJsonValueString("handler", jsonObject, handler);
            Core::JsonUtils::GetJsonValueLong("memorySize", jsonObject, memorySize);
            Core::JsonUtils::GetJsonValueLong("codeSize", jsonObject, codeSize);
            Core::JsonUtils::GetJsonValueString("imageId", jsonObject, imageId);
            Core::JsonUtils::GetJsonValueString("containerId", jsonObject, containerId);
            Core::JsonUtils::GetJsonValueString("arn", jsonObject, arn);
            Core::JsonUtils::GetJsonValueString("codeSha256", jsonObject, codeSha256);
            Core::JsonUtils::GetJsonValueInt("timeout", jsonObject, timeout);
            Core::JsonUtils::GetJsonValueInt("concurrency", jsonObject, concurrency);
            Core::JsonUtils::GetJsonValueString("stateReason", jsonObject, stateReason);
            Core::JsonUtils::GetJsonValueDate("lastStarted", jsonObject, lastStarted);
            Core::JsonUtils::GetJsonValueDate("lastInvocation", jsonObject, lastInvocation);
            std::string tmp;
            Core::JsonUtils::GetJsonValueString("arn", jsonObject, tmp);
            if (!tmp.empty()) {
                state = LambdaStateFromString(tmp);
            }

            // Ephemeral storage
            if (jsonObject->has("ephemeralStorage")) {
                ephemeralStorage.FromJsonObject(jsonObject->getObject("ephemeralStorage"));
            }

            // Environment
            if (jsonObject->has("environment")) {
                environment.FromJsonObject(jsonObject->getObject("environment"));
            }

        } catch (Poco::Exception &e) {
            log_error << "JSON Exception" << e.message();
            throw Core::JsonException(e.message());
        }
    }

    std::string Lambda::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Lambda &l) {
        os << "Lambda=" << bsoncxx::to_json(l.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Lambda