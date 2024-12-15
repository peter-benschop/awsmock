//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/Lambda.h>

namespace AwsMock::Database::Entity::Lambda {

    bool Lambda::HasEventSource(const std::string &eventSourceArn) const {
        return std::ranges::find_if(eventSources, [eventSourceArn](const EventSourceMapping &e) {
                   return e.eventSourceArn == eventSourceArn;
               }) != eventSources.end();
    }

    bool Lambda::HasTag(const std::string &key) const {
        return std::ranges::find_if(tags, [key](const std::pair<std::string, std::string> &t) {
                   return t.first == key;
               }) != tags.end();
    }

    std::string Lambda::GetTagValue(const std::string &key) const {
        const auto it = std::ranges::find_if(tags, [key](const std::pair<std::string, std::string> &t) {
            return t.first == key;
        });
        return it->second;
    }

    Instance Lambda::GetInstance(const std::string &instanceId) {
        if (const auto it = std::ranges::find(instances, instanceId, &Instance::id); it != instances.end()) {
            return *it;
        }
        log_error << "Lambda instance not found, id: " << instanceId;
        return {};
    }

    void Lambda::RemoveInstance(const Instance &instance) {
        std::string id = instance.id;
        instances.erase(std::ranges::remove_if(instances, [&id](const Instance &instance) { return id == instance.id; }).begin(), instances.end());
    }

    view_or_value<view, value> Lambda::ToDocument() const {

        // Convert instances
        auto instancesDoc = array{};
        for (const auto &instance: instances) {
            instancesDoc.append(instance.ToDocument());
        }

        // Convert environment to document
        auto variablesDoc = array{};
        for (const auto &[fst, snd]: environment.variables) {
            variablesDoc.append(make_document(kvp(fst, snd)));
        }
        view_or_value<view, value> varDoc = make_document(kvp("variables", variablesDoc));

        // Convert tags to document
        auto tagsDoc = document{};
        for (const auto &[fst, snd]: tags) {
            tagsDoc.append(kvp(fst, snd));
        }

        // Convert event source mappings
        auto eventSourcesDoc = array{};
        for (const auto &e: eventSources) {
            eventSourcesDoc.append(e.ToDocument());
        }

        view_or_value<view, value> ephemeralStorageDoc = make_document(kvp("size", static_cast<bsoncxx::types::b_int64>(ephemeralStorage.size)));

        document lambdaDoc;
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
                kvp("imageSize", imageSize),
                kvp("containerId", containerId),
                kvp("containerSize", containerSize),
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

    void Lambda::FromDocument(const std::optional<view> &mResult) {

        oid = Core::Bson::BsonUtils::GetOidValue(mResult, "_id");
        region = Core::Bson::BsonUtils::GetStringValue(mResult, "region");
        user = Core::Bson::BsonUtils::GetStringValue(mResult, "user");
        function = Core::Bson::BsonUtils::GetStringValue(mResult, "function");
        runtime = Core::Bson::BsonUtils::GetStringValue(mResult, "runtime");
        role = Core::Bson::BsonUtils::GetStringValue(mResult, "role");
        handler = Core::Bson::BsonUtils::GetStringValue(mResult, "handler");
        memorySize = Core::Bson::BsonUtils::GetLongValue(mResult, "memorySize");
        ephemeralStorage.FromDocument(mResult.value()["ephemeralStorage"].get_document().value);
        codeSize = Core::Bson::BsonUtils::GetLongValue(mResult, "codeSize");
        imageId = Core::Bson::BsonUtils::GetStringValue(mResult, "imageId");
        imageSize = Core::Bson::BsonUtils::GetLongValue(mResult, "imageSize");
        containerId = Core::Bson::BsonUtils::GetStringValue(mResult, "containerId");
        containerSize = Core::Bson::BsonUtils::GetLongValue(mResult, "containerSize");
        arn = Core::Bson::BsonUtils::GetStringValue(mResult, "arn");
        codeSha256 = Core::Bson::BsonUtils::GetStringValue(mResult, "codeSha256");
        timeout = Core::Bson::BsonUtils::GetIntValue(mResult, "timeout");
        concurrency = Core::Bson::BsonUtils::GetIntValue(mResult, "concurrency");
        state = LambdaStateFromString(Core::Bson::BsonUtils::GetStringValue(mResult, "state"));
        stateReason = Core::Bson::BsonUtils::GetStringValue(mResult, "stateReason");
        stateReasonCode = LambdaStateReasonCodeFromString(Core::Bson::BsonUtils::GetStringValue(mResult, "stateReasonCode"));
        lastStarted = Core::Bson::BsonUtils::GetDateValue(mResult.value()["lastStarted"]);
        lastInvocation = Core::Bson::BsonUtils::GetDateValue(mResult.value()["lastInvocation"]);
        invocations = Core::Bson::BsonUtils::GetLongValue(mResult, "invocations");
        averageRuntime = Core::Bson::BsonUtils::GetLongValue(mResult, "averageRuntime");
        created = Core::Bson::BsonUtils::GetDateValue(mResult, "created");
        modified = Core::Bson::BsonUtils::GetDateValue(mResult, "modified");

        // Environment
        environment.FromDocument(mResult.value()["environment"].get_document().value);

        // Get tags
        if (mResult.value().find("tags") != mResult.value().end()) {
            for (const view tagsView = mResult.value()["tags"].get_document().value; const bsoncxx::document::element &tagElement: tagsView) {
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
            for (const view instancesView = mResult.value()["instances"].get_array().value; const bsoncxx::document::element &instanceElement: instancesView) {
                Instance instance;
                instance.FromDocument(instanceElement.get_document().view());
                instances.emplace_back(instance);
            }
        }

        // Get event sources
        if (mResult.value().find("eventSources") != mResult.value().end()) {
            for (const view eventSourcesView = mResult.value()["eventSources"].get_array().value; const bsoncxx::document::element &eventSourceElement: eventSourcesView) {
                EventSourceMapping eventSourceMapping;
                eventSourceMapping.FromDocument(eventSourceElement.get_document().view());
                eventSources.emplace_back(eventSourceMapping);
            }
        }
    }

    std::string Lambda::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string Lambda::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Lambda &l) {
        os << "Lambda=" << to_json(l.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Lambda