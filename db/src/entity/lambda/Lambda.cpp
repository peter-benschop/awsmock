//
// Created by vogje01 on 03/09/2023.
//

#include "awsmock/entity/lambda/Lambda.h"

namespace AwsMock::Database::Entity::Lambda {

    view_or_value <view, value> Lambda::ToDocument() const {

        // Convert environment to document
        auto variablesDoc = bsoncxx::builder::basic::array{};
        for (const auto &variables : environment.variables) {
            variablesDoc.append(make_document(kvp(variables.first, variables.second)));
        }
        view_or_value <view, value> varDoc = make_document(kvp("variables", variablesDoc));

        // Convert tags to document
        auto tagsDoc = bsoncxx::builder::basic::document{};
        for (const auto &t : tags.tags) {
            tagsDoc.append(kvp(t.first, t.second));
        }

        view_or_value <view, value> ephemeralStorageDoc = make_document(kvp("size", ephemeralStorage.size));

        view_or_value <view, value> lambdaDoc = make_document(
            kvp("region", region),
            kvp("user", user),
            kvp("function", function),
            kvp("runtime", runtime),
            kvp("role", role),
            kvp("handler", handler),
            kvp("memorySize", memorySize),
            kvp("ephemeralStorage", ephemeralStorageDoc),
            kvp("codeSize", codeSize),
            kvp("fileName", fileName),
            kvp("imageId", imageId),
            kvp("containerId", containerId),
            kvp("tags", tagsDoc),
            kvp("arn", arn),
            kvp("hostPort", hostPort),
            kvp("timeout", timeout),
            kvp("codeSha256", codeSha256),
            kvp("environment", varDoc),
            kvp("state", LambdaStateToString(state)),
            kvp("stateReason", stateReason),
            kvp("stateReasonCode", LambdaStateReasonCodeToString(stateReasonCode)),
            kvp("lastStarted", bsoncxx::types::b_date(std::chrono::milliseconds(lastStarted.timestamp().epochMicroseconds() / 1000))),
            kvp("lastInvocation", bsoncxx::types::b_date(std::chrono::milliseconds(lastInvocation.timestamp().epochMicroseconds() / 1000))),
            kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
            kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

        return lambdaDoc;
    }

    void Lambda::FromDocument(mongocxx::stdx::optional <bsoncxx::document::value> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        region = mResult.value()["region"].get_string().value.to_string();
        user = mResult.value()["user"].get_string().value.to_string();
        function = mResult.value()["function"].get_string().value.to_string();
        runtime = mResult.value()["runtime"].get_string().value.to_string();
        role = mResult.value()["role"].get_string().value.to_string();
        handler = mResult.value()["handler"].get_string().value.to_string();
        memorySize = mResult.value()["memorySize"].get_int64().value;
        ephemeralStorage.FromDocument(mResult.value()["ephemeralStorage"].get_document().value);
        codeSize = mResult.value()["codeSize"].get_int64().value;
        fileName = mResult.value()["fileName"].get_string().value.to_string();
        imageId = mResult.value()["imageId"].get_string().value.to_string();
        containerId = mResult.value()["containerId"].get_string().value.to_string();
        tags.FromDocument(mResult.value()["tags"].get_document().value);
        arn = mResult.value()["arn"].get_string().value.to_string();
        codeSha256 = mResult.value()["codeSha256"].get_string().value.to_string();
        hostPort = mResult.value()["hostPort"].get_int32().value;
        timeout = mResult.value()["timeout"].get_int32().value;
        environment.FromDocument(mResult.value()["environment"].get_document().value);
        state = LambdaStateFromString(mResult.value()["state"].get_string().value.to_string());
        stateReason = mResult.value()["stateReason"].get_string().value.to_string();
        stateReasonCode = LambdaStateReasonCodeFromString(mResult.value()["stateReasonCode"].get_string().value.to_string());
        lastStarted = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date().value) / 1000));
        lastInvocation = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["lastInvocation"].get_date().value) / 1000));
        created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
        modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));
    }

    void Lambda::FromDocument(mongocxx::stdx::optional <bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        region = mResult.value()["region"].get_string().value.to_string();
        user = mResult.value()["user"].get_string().value.to_string();
        function = mResult.value()["function"].get_string().value.to_string();
        runtime = mResult.value()["runtime"].get_string().value.to_string();
        role = mResult.value()["role"].get_string().value.to_string();
        handler = mResult.value()["handler"].get_string().value.to_string();
        memorySize = mResult.value()["memorySize"].get_int64().value;
        ephemeralStorage.FromDocument(mResult.value()["ephemeralStorage"].get_document().value);
        codeSize = mResult.value()["codeSize"].get_int64().value;
        fileName = mResult.value()["fileName"].get_string().value.to_string();
        imageId = mResult.value()["imageId"].get_string().value.to_string();
        containerId = mResult.value()["containerId"].get_string().value.to_string();
        tags.FromDocument(mResult.value()["tags"].get_document().value);
        arn = mResult.value()["arn"].get_string().value.to_string();
        codeSha256 = mResult.value()["codeSha256"].get_string().value.to_string();
        hostPort = mResult.value()["hostPort"].get_int32().value;
        timeout = mResult.value()["timeout"].get_int32().value;
        environment.FromDocument(mResult.value()["environment"].get_document().value);
        state = LambdaStateFromString(mResult.value()["state"].get_string().value.to_string());
        stateReason = mResult.value()["stateReason"].get_string().value.to_string();
        stateReasonCode = LambdaStateReasonCodeFromString(mResult.value()["stateReasonCode"].get_string().value.to_string());
        lastStarted = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date().value) / 1000));
        lastInvocation = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["lastInvocation"].get_date().value) / 1000));
        created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
        modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));
    }

    std::string Lambda::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Lambda &l) {
        os << "Lambda={oid='" << l.oid << "' region='" << l.region << "' function='" << l.function << "'runtime='" << l.runtime << "' role='" << l.role <<
           "' handler='" << l.handler << "' imageId='" << l.imageId << "' containerId='" << l.containerId << "'" << l.tags.ToString() << " arn='" << l.arn <<
           "' hostPort='" << l.hostPort << "' timeout='" << l.timeout << "' state='" << l.state << "' stateReason='" << l.stateReason << "' stateReasonCode='" << l.stateReasonCode <<
           "' memorySize='" << l.memorySize << "' ephemeralStorage={" << l.ephemeralStorage.ToString() << "}" << "' codeSize='" << l.codeSize << "' fileName "
           << l.fileName << "' lastStarted='" << Poco::DateTimeFormatter().format(l.lastStarted, Poco::DateTimeFormat::HTTP_FORMAT) <<
           "' created='" << Poco::DateTimeFormatter().format(l.created, Poco::DateTimeFormat::HTTP_FORMAT) <<
           "' modified='" << Poco::DateTimeFormatter().format(l.modified, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
        return os;
    }
}