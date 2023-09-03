//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_CREATEFUNCTIONREQUEST_H
#define AWSMOCK_DTO_LAMBDA_CREATEFUNCTIONREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>
#include <utility>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/dto/lambda/Environment.h>
#include <awsmock/dto/lambda/EphemeralStorage.h>

namespace AwsMock::Dto::Lambda {

    struct Code {

      /**
       * Image URI
       */
      std::string imageUri;

      /**
       * S3 bucket
       */
      std::string s3Bucket;

      /**
       * S3 key
       */
      std::string s3Key;

      /**
       * S3 object version
       */
      std::string s3ObjectVersion;

      /**
       * Zipped function code.
       *
       * <p>The base64-encoded contents of the deployment package. AWS SDK and AWS CLI clients handle the encoding for you.</p>
       */
      std::string zipFile;

      /**
       * Convert from a JSON object.
       *
       * @param jsonObject json object
       */
      void FromJson(Poco::JSON::Object::Ptr jsonObject) {
          try {
              Core::JsonUtils::GetJsonValueString("S3Bucket", jsonObject, s3Bucket);
              Core::JsonUtils::GetJsonValueString("S3Key", jsonObject, s3Key);
              Core::JsonUtils::GetJsonValueString("S3ObjectVersion", jsonObject, s3ObjectVersion);
              Core::JsonUtils::GetJsonValueString("ImageUri", jsonObject, imageUri);
              Core::JsonUtils::GetJsonValueString("ZipFile", jsonObject, zipFile);
          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Creates a JSON string from the object.
       *
       * @return JSON string
       */
      [[nodiscard]] Poco::JSON::Object ToJson() const {

          Poco::JSON::Object rootObject;
          try {
              rootObject.set("ZipFile", zipFile);
              rootObject.set("S3Bucket", s3Bucket);
              rootObject.set("S3Key", s3Key);
              rootObject.set("S3ObjectVersion", s3ObjectVersion);
              rootObject.set("ImageUri", imageUri);

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
          return rootObject;
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
      friend std::ostream &operator<<(std::ostream &os, const Code &r) {
          os << "Code={imageUri='" << r.s3Bucket << "' imageUri='" << r.s3Bucket << "' s3Key='" << r.s3Key << "' s3ObjectVersion='" << r.s3ObjectVersion + "'}";
          return os;
      }

    };

    struct CreateFunctionRequest {

      /**
       * Region
       */
      std::string region;

      /**
       * User
       */
      std::string user;

      /**
       * Name of the function
       */
      std::string functionName;

      /**
       * Runtime environment
       */
      std::string runtime;

      /**
       * Role
       */
      std::string role;

      /**
       * Role
       */
      std::string handler;

      /**
       * Environment
       */
      EnvironmentVariables environmentVariables;

      /**
       * Memory size in MB. Default: 128, Range: 128 - 10240 MB
       */
      long memorySize = 128;

      /**
       * Temporary disk space in MB
       */
      EphemeralStorage ephemeralStorage;

      /**
       * Code
       */
      Code code;

      /**
       * Tags
       */
      Tags tags;

      /**
       * Creates a JSON string from the object.
       *
       * @return JSON string
       */
      [[nodiscard]] std::string ToJson() const {

          try {
              Poco::JSON::Object rootJson;
              rootJson.set("Region", region);
              rootJson.set("User", user);
              rootJson.set("FunctionName", functionName);
              rootJson.set("Runtime", runtime);
              rootJson.set("Role", role);
              rootJson.set("Handler", handler);
              rootJson.set("MemorySize", memorySize);
              rootJson.set("Code", code.ToJson());

              std::ostringstream os;
              rootJson.stringify(os);
              return os.str();

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
      }

      /**
       * Parse a JSON stream
       *"{\"JAVA_TOOL_OPTIONS\":\"-Duser.timezone=Europe/Berlin -Dspring.profiles.active=localhost\"}"
       * @param body jsoninput stream
       * @return
       */
      void FromJson(const std::string &body) {

          Poco::JSON::Parser parser;
          Poco::Dynamic::Var result = parser.parse(body);
          Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

          try {
              Core::JsonUtils::GetJsonValueString("FunctionName", rootObject, functionName);
              Core::JsonUtils::GetJsonValueString("Runtime", rootObject, runtime);
              Core::JsonUtils::GetJsonValueString("Role", rootObject, role);
              Core::JsonUtils::GetJsonValueString("Handler", rootObject, handler);

              // Tags
              if (rootObject->has("Tags")) {
                  tags.FromJson(rootObject->getObject("Tags"));
              }

              // EphemeralStorage
              if (rootObject->has("EphemeralStorage")) {
                  ephemeralStorage.FromJson(rootObject->getObject("EphemeralStorage"));
              }

              // Environment
              if (rootObject->has("Environment")) {
                  environmentVariables.FromJson(rootObject->getObject("Environment"));
              }

              // Code
              if (rootObject->has("Code")) {
                  code.FromJson(rootObject->getObject("Code"));
              }

              // Cleanup
              rootObject->clear();
              parser.reset();

          } catch (Poco::Exception &exc) {
              throw Core::ServiceException(exc.message(), 500);
          }
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
      friend std::ostream &operator<<(std::ostream &os, const CreateFunctionRequest &r) {
          os << "CreateFunctionRequest={region='" << r.region << "' user='" << r.user << "' functionName='" << r.functionName << "' runtime: '" << r.runtime <<
             "' role='" << r.role << "' handler='" << r.handler << "' memorySize='" << r.memorySize << "' ephemeralStorage='" << r.ephemeralStorage << "' tags='"
             << r.tags << "' environment={" << r.environmentVariables.ToString() << "} code={" << r.code.ToString() << "}}";
          return os;
      }
    };

} // namespace AwsMock::Dto::Lambda

#endif // AWSMOCK_DTO_LAMBDA_CREATEFUNCTIONREQUEST_H
