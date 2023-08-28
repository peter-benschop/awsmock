//
// Created by vogje01 on 07/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_LAMBDA_H
#define AWSMOCK_DB_ENTITY_LAMBDA_H

// C++ includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

namespace AwsMock::Database::Entity::Lambda {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::view_or_value;
    using bsoncxx::document::view;
    using bsoncxx::document::value;

    enum LambdaState {
      PENDING,
      ACTIVE,
      INACTIVE,
      FAILED
    };

    static std::map<LambdaState,std::string> LambdaStateNames{
        {LambdaState::PENDING, "PENDING"},
        {LambdaState::ACTIVE, "ACTIVE"},
        {LambdaState::INACTIVE, "INACTIVE"},
        {LambdaState::FAILED, "FAILED"},
    };

    static std::string LambdaStateToString(LambdaState lambdaState) {
        return LambdaStateNames[lambdaState];
    }

    static LambdaState LambdaStateFromString(const std::string &lambdaState) {
        for(auto &it : LambdaStateNames) {
            if(it.second == lambdaState) {
                return it.first;
            }
        }
        return LambdaState::INACTIVE;
    }

    enum LambdaStateReasonCode {
      Idle,
      Creating,
      Restoring,
      EniLimitExceeded,
      InsufficientRolePermissions,
      InvalidConfiguration,
      InternalError,
      SubnetOutOfIPAddresses,
      InvalidSubnet,
      InvalidSecurityGroup,
      ImageDeleted,
      ImageAccessDenied,
      InvalidImage,
      KMSKeyAccessDenied,
      KMSKeyNotFound,
      InvalidStateKMSKey,
      DisabledKMSKey,
      EFSIOError,
      EFSMountConnectivityError,
      EFSMountFailure,
      EFSMountTimeout,
      InvalidRuntime,
      InvalidZipFileException,
      FunctionError
    };

    static std::map<LambdaStateReasonCode,std::string> LambdaStateReasonCodeNames{
        {LambdaStateReasonCode::Idle, "Idle"},
        {LambdaStateReasonCode::Creating, "Creating"},
        {LambdaStateReasonCode::Restoring, "Restoring"},
        {LambdaStateReasonCode::EniLimitExceeded, "EniLimitExceeded"},
        {LambdaStateReasonCode::InsufficientRolePermissions, "InsufficientRolePermissions"},
        {LambdaStateReasonCode::InvalidConfiguration, "InvalidConfiguration"},
        {LambdaStateReasonCode::InternalError, "InternalError"},
        {LambdaStateReasonCode::SubnetOutOfIPAddresses, "SubnetOutOfIPAddresses"},
        {LambdaStateReasonCode::InvalidSubnet, "InvalidSubnet"},
        {LambdaStateReasonCode::InvalidSecurityGroup, "InvalidSecurityGroup"},
        {LambdaStateReasonCode::ImageDeleted, "ImageDeleted"},
        {LambdaStateReasonCode::ImageAccessDenied, "ImageAccessDenied"},
        {LambdaStateReasonCode::InvalidImage, "InvalidImage"},
        {LambdaStateReasonCode::KMSKeyAccessDenied, "KMSKeyAccessDenied"},
        {LambdaStateReasonCode::KMSKeyNotFound, "KMSKeyNotFound"},
        {LambdaStateReasonCode::InvalidStateKMSKey, "InvalidStateKMSKey"},
        {LambdaStateReasonCode::DisabledKMSKey, "DisabledKMSKey"},
        {LambdaStateReasonCode::EFSIOError, "EFSIOError"},
        {LambdaStateReasonCode::EFSMountConnectivityError, "EFSMountConnectivityError"},
        {LambdaStateReasonCode::EFSMountFailure, "EFSMountFailure"},
        {LambdaStateReasonCode::EFSMountTimeout, "EFSMountTimeout"},
        {LambdaStateReasonCode::InvalidRuntime, "InvalidRuntime"},
        {LambdaStateReasonCode::InvalidZipFileException, "InvalidZipFileException"},
        {LambdaStateReasonCode::FunctionError, "FunctionError"},
    };

    static std::string LambdaStateReasonCodeToString(LambdaStateReasonCode lambdaStateReasonCode) {
        return LambdaStateReasonCodeNames[lambdaStateReasonCode];
    }

    static LambdaStateReasonCode LambdaStateReasonCodeFromString(const std::string &lambdaStateReasonCode) {
        for(auto &it : LambdaStateReasonCodeNames) {
            if(it.second == lambdaStateReasonCode) {
                return it.first;
            }
        }
        return LambdaStateReasonCode::Idle;
    }

    struct Environment {

      /**
       * Variables
       */
      std::vector<std::pair<std::string, std::string>> variables;

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

          auto varDoc = mResult.value()["variables"].get_array();
          for (auto &v : varDoc.value) {
              for (auto &it : v.get_document().value) {
                  variables.emplace_back(std::make_pair(it.key().to_string(), it.get_string().value.to_string()));
              }
          }
      }
    };

    struct Lambda {

      /**
       * ID
       */
      std::string oid;

      /**
       * AWS region name
       */
      std::string region;

      /**
       * User
       */
      std::string user;

      /**
       * Function
       */
      std::string function;

      /**
       * Runtime
       */
      std::string runtime;

      /**
       * Role
       */
      std::string role;

      /**
       * Handler
       */
      std::string handler;

      /**
       * Size
       */
      long size;

      /**
       * Image ID
       */
      std::string imageId;

      /**
       * Container ID
       */
      std::string containerId;

      /**
       * Tag
       */
      std::string tag;

      /**
       * ARN
       */
      std::string arn;

      /**
       * Random host port
       */
      int hostPort;

      /**
       * Environment
       */
      Environment environment;

      /**
       * Lambda state
       */
      LambdaState state = LambdaState::PENDING;

      /**
       * State reason
       */
      std::string stateReason;

      /**
       * State reason code
       */
      LambdaStateReasonCode stateReasonCode = LambdaStateReasonCode::Creating;

      /**
       * Code SHA256
       */
      std::string codeSha256;

      /**
       * Last function start
       */
      Poco::DateTime lastStarted;

      /**
       * Creation date
       */
      Poco::DateTime created = Poco::DateTime();

      /**
       * Last modification date
       */
      Poco::DateTime modified = Poco::DateTime();

      /**
       * Converts the entity to a MongoDB document
       *
       * @return entity as MongoDB document.
       */
      [[nodiscard]] view_or_value<view, value> ToDocument() const {

          // Convert environment to document
          auto variablesDoc = bsoncxx::builder::basic::array{};
          for (const auto &variables : environment.variables) {
              variablesDoc.append(make_document(kvp(variables.first, variables.second)));
          }
          view_or_value<view, value> varDoc = make_document(kvp("variables", variablesDoc));

          view_or_value<view, value> lambdaDoc = make_document(
              kvp("region", region),
              kvp("user", user),
              kvp("function", function),
              kvp("runtime", runtime),
              kvp("role", role),
              kvp("handler", handler),
              kvp("size", size),
              kvp("imageId", imageId),
              kvp("containerId", containerId),
              kvp("tag", tag),
              kvp("arn", arn),
              kvp("hostPort", hostPort),
              kvp("codeSha256", codeSha256),
              kvp("environment", varDoc),
              kvp("state", LambdaStateToString(state)),
              kvp("stateReason", stateReason),
              kvp("stateReasonCode", LambdaStateReasonCodeToString(stateReasonCode)),
              kvp("lastStarted", bsoncxx::types::b_date(std::chrono::milliseconds(lastStarted.timestamp().epochMicroseconds() / 1000))),
              kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
              kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

          return lambdaDoc;
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      void FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

          oid = mResult.value()["_id"].get_oid().value.to_string();
          region = mResult.value()["region"].get_string().value.to_string();
          user = mResult.value()["user"].get_string().value.to_string();
          function = mResult.value()["function"].get_string().value.to_string();
          runtime = mResult.value()["runtime"].get_string().value.to_string();
          role = mResult.value()["role"].get_string().value.to_string();
          handler = mResult.value()["handler"].get_string().value.to_string();
          size = mResult.value()["size"].get_int64().value;
          imageId = mResult.value()["imageId"].get_string().value.to_string();
          containerId = mResult.value()["containerId"].get_string().value.to_string();
          tag = mResult.value()["tag"].get_string().value.to_string();
          arn = mResult.value()["arn"].get_string().value.to_string();
          codeSha256 = mResult.value()["codeSha256"].get_string().value.to_string();
          hostPort = mResult.value()["hostPort"].get_int32().value;
          environment.FromDocument(mResult.value()["environment"].get_document().value);
          state = LambdaStateFromString(mResult.value()["state"].get_string().value.to_string());
          stateReason = mResult.value()["stateReason"].get_string().value.to_string();
          stateReasonCode = LambdaStateReasonCodeFromString(mResult.value()["stateReasonCode"].get_string().value.to_string());
          lastStarted = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date().value) / 1000));
          created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
          modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

          oid = mResult.value()["_id"].get_oid().value.to_string();
          region = mResult.value()["region"].get_string().value.to_string();
          user = mResult.value()["user"].get_string().value.to_string();
          function = mResult.value()["function"].get_string().value.to_string();
          runtime = mResult.value()["runtime"].get_string().value.to_string();
          role = mResult.value()["role"].get_string().value.to_string();
          handler = mResult.value()["handler"].get_string().value.to_string();
          size = mResult.value()["size"].get_int64().value;
          imageId = mResult.value()["imageId"].get_string().value.to_string();
          containerId = mResult.value()["containerId"].get_string().value.to_string();
          tag = mResult.value()["tag"].get_string().value.to_string();
          arn = mResult.value()["arn"].get_string().value.to_string();
          codeSha256 = mResult.value()["codeSha256"].get_string().value.to_string();
          hostPort = mResult.value()["hostPort"].get_int32().value;
          environment.FromDocument(mResult.value()["environment"].get_document().value);
          state = LambdaStateFromString(mResult.value()["state"].get_string().value.to_string());
          stateReason = mResult.value()["stateReason"].get_string().value.to_string();
          stateReasonCode = LambdaStateReasonCodeFromString(mResult.value()["stateReasonCode"].get_string().value.to_string());
          lastStarted = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date().value) / 1000));
          created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
          modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const Lambda &m) {
          os << "Lambda={oid='" << m.oid << "' region='" << m.region << "' function='" << m.function << "'runtime='" << m.runtime << "' role='" << m.role <<
             "' handler='" << m.handler << "' imageId='" << m.imageId << "' containerId='" << m.containerId << "' tag='" << m.tag << "' arn='" << m.arn <<
             "' hostPort='" << m.hostPort << "' state='" << m.state << "' stateReason='" << m.stateReason << "' stateReasonCode='" << m.stateReasonCode <<
             "' lastStarted='" << Poco::DateTimeFormatter().format(m.lastStarted, Poco::DateTimeFormat::HTTP_FORMAT) <<
             "' created='" << Poco::DateTimeFormatter().format(m.created, Poco::DateTimeFormat::HTTP_FORMAT) <<
             "' modified='" << Poco::DateTimeFormatter().format(m.modified, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
          return os;
      }

    };

    typedef struct Lambda Lambda;
    typedef std::vector<Lambda> LambdaList;
}
#endif //AWSMOCK_DB_ENTITY_LAMBDA_H
