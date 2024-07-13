//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/core/AwsUtils.h>

namespace AwsMock::Core {

    std::string AwsUtils::CreateS3Arn(const std::string &region, const std::string &accountId, const std::string &bucket, const std::string &key) {
        return CreateArn("s3", region, accountId, bucket + "/" + key);
    }

    std::string AwsUtils::CreateLambdaArn(const std::string &region, const std::string &accountId, const std::string &function) {
        return CreateArn("lambda", region, accountId, "function:" + function);
    }

    std::string AwsUtils::ConvertSQSQueueArnToUrl(const std::string &queueArn) {

        std::string endpoint = GetEndpoint();
        std::vector<std::string> parts = StringUtils::Split(queueArn, ':');
        if (parts.size() < 6) {
            log_error << "Could not convert SQS arn to url, arn: " << queueArn;
            return {};
        }

        std::string accountId = parts[4];
        std::string queueName = parts[5];
        parts.clear();

        std::string region = Core::Configuration::instance().getString("awsmock.region");
        std::string port = Core::Configuration::instance().getString("awsmock.service.gateway.http.port");
        std::string hostname = Core::Configuration::instance().getString("awsmock.service.sqs.hostname", SystemUtils::GetHostName());

        return "http://sqs." + region + "." + hostname + ":" + port + "/" + accountId + "/" + queueName;
    }

    std::string AwsUtils::CreateSQSQueueArn(const std::string &region, const std::string &accountId, const std::string &queueName) {
        return CreateArn("sqs", region, accountId, queueName);
    }

    std::string AwsUtils::CreateSNSTopicArn(const std::string &region, const std::string &accountId, const std::string &topicName) {
        return CreateArn("sns", region, accountId, topicName);
    }

    std::string AwsUtils::CreateSNSSubscriptionArn(const std::string &region, const std::string &accountId, const std::string &topicName) {
        return CreateArn("sns", region, accountId, topicName + ":" + Poco::UUIDGenerator().createRandom().toString());
    }

    std::string AwsUtils::CreateTransferArn(const std::string &region, const std::string &accountId, const std::string &serverId) {
        return CreateArn("transfer", region, accountId, "manager/" + serverId);
    }

    std::string AwsUtils::CreateTransferUserArn(const std::string &region, const std::string &accountId, const std::string &serverId, const std::string &userName) {
        return CreateArn("transfer", region, accountId, serverId + "/" + userName);
    }

    std::string AwsUtils::CreateSecretArn(const std::string &region, const std::string &accountId, const std::string &secretId) {
        return CreateArn("secretsmanager", region, accountId, "secret:" + secretId);
    }

    std::string AwsUtils::CreateKMSKeyArn(const std::string &region, const std::string &accountId, const std::string &keyId) {
        return CreateArn("kms", region, accountId, "key/" + keyId);
    }

    std::string AwsUtils::CreateCognitoUserPoolId(const std::string &region) {
        return region + "_" + Core::StringUtils::GenerateRandomString(9);
    }

    std::string AwsUtils::CreateCognitoUserPoolArn(const std::string &region, const std::string &accountId, const std::string &userPoolId) {
        return CreateArn("cognito-idp", region, accountId, userPoolId);
    }

    std::string AwsUtils::CreateRequestId() {
        std::stringstream stringstream;
        stringstream << boost::uuids::random_generator()();
        return stringstream.str();
    }

    std::string AwsUtils::CreateMessageId() {
        std::stringstream stringstream;
        stringstream << boost::uuids::random_generator()();
        return stringstream.str();
    }

    std::string AwsUtils::GetS3BucketName(const http::request<http::dynamic_body> &request) {
        if (IsS3HostStyle(request)) {
            return GetS3HostStyleBucket(request);
        } else {
            return GetS3PathStyleBucket(request);
        }
    }

    std::string AwsUtils::GetS3ObjectKey(const http::request<http::dynamic_body> &request) {
        if (IsS3HostStyle(request)) {
            return GetS3HostStyleObjectKey(request);
        } else {
            return GetS3PathStyleObjectKey(request);
        }
    }

    bool AwsUtils::IsS3HostStyle(const http::request<http::dynamic_body> &request) {
        if (request.base().find(http::field::host) != request.end()) {
            std::string host = request.base()[http::field::host];
            return Core::StringUtils::Contains(host, ".s3.");
        }
        return false;
    }

    std::string AwsUtils::GetS3HostStyleBucket(const http::request<http::dynamic_body> &request) {
        if (request.base().find(http::field::host) != request.end()) {
            std::string host = request.base()[http::field::host];
            return Core::StringUtils::SubStringUntil(host, ".");
        }
        return {};
    }

    std::string AwsUtils::GetS3PathStyleBucket(const http::request<http::dynamic_body> &request) {
        return Core::HttpUtils::GetPathParameter(request.target(), 0);
    }

    std::string AwsUtils::GetS3HostStyleObjectKey(const http::request<http::dynamic_body> &request) {
        return Core::HttpUtils::GetPathParametersFromIndex(request.target(), 0);
    }

    std::string AwsUtils::GetS3PathStyleObjectKey(const http::request<http::dynamic_body> &request) {
        return Core::HttpUtils::GetPathParametersFromIndex(request.target(), 1);
    }

    void AwsUtils::AddAuthorizationHeader(http::request<http::dynamic_body> &request, const std::string &module, const std::string &contentType, const std::string &signedHeaders, const std::string &payload) {

        Core::Configuration &configuration = Core::Configuration::instance();
        std::string region = configuration.getString("awsmock.region", "eu-central-1");
        std::string accessKeyId = configuration.getString("awsmock.access.key.id", "none");
        std::string secretAccessKey = configuration.getString("awsmock.secret.access.key", "none");

        // Mandatory headers
        request.set(http::field::host, Core::SystemUtils::GetHostName());
        request.set(http::field::content_type, contentType);
        request.set("x-amz-content-sha256", Core::Crypto::GetSha256FromString(payload));
        request.set("x-amz-date", GetISODateString());
        request.set("x-amz-security-token", secretAccessKey);

        std::string dateString = GetDateString();
        std::string requestVersion = "aws4_request";
        std::string scope = dateString + "/" + region + "/" + module + "/" + requestVersion;

        AuthorizationHeaderKeys authorizationHeaderKeys = {.signingVersion = "AWS4-HMAC-SHA256", .secretAccessKey = secretAccessKey, .dateTime = dateString, .isoDateTime = GetISODateString(), .scope = scope, .region = region, .module = module, .requestVersion = requestVersion, .signedHeaders = signedHeaders};
        std::string canonicalRequest = GetCanonicalRequest(request, authorizationHeaderKeys);
        std::string stringToSign = GetStringToSign(canonicalRequest, authorizationHeaderKeys);
        std::string signature = GetSignature(authorizationHeaderKeys, stringToSign);

        std::string authorization = "AWS4-HMAC-SHA256 Credential=" + accessKeyId + "/" + dateString + "/" + region + "/" + module + "/" + requestVersion + ",SignedHeaders=" + signedHeaders + ",Signature=" + signature;
        request.set(http::field::authorization, authorization);
    }

    void AwsUtils::AddAuthorizationHeader(const std::string &method, const std::string &path, std::map<std::string, std::string> &headers, const std::string &module, const std::string &contentType, const std::string &signedHeaders, const std::string &payload) {

        Core::Configuration &configuration = Core::Configuration::instance();
        std::string region = configuration.getString("awsmock.region", "eu-central-1");
        std::string accessKeyId = configuration.getString("awsmock.access.key.id", "none");
        std::string secretAccessKey = configuration.getString("awsmock.secret.access.key", "none");

        // Mandatory headers
        if (headers.find("Host") == headers.end()) {
            headers["Host"] = Core::SystemUtils::GetHostName();
        }
        headers["Content-Type"] = contentType;
        headers["X-Amz-Content-Sha256"] = Core::Crypto::GetSha256FromString(payload);
        if (headers.find("X-Amz-Date") == headers.end()) {
            headers["X-Amz-Date"] = GetISODateString();
        }
        headers["X-Amz-Security-Token"] = secretAccessKey;

        std::string dateString = GetDateString();
        std::string requestVersion = "aws4_request";
        std::string scope = dateString + "/" + region + "/" + module + "/" + requestVersion;

        AuthorizationHeaderKeys authorizationHeaderKeys = {.signingVersion = "AWS4-HMAC-SHA256", .secretAccessKey = secretAccessKey, .dateTime = dateString, .isoDateTime = GetISODateString(), .scope = scope, .region = region, .module = module, .requestVersion = requestVersion, .signedHeaders = signedHeaders};
        std::string canonicalRequest = GetCanonicalRequest(method, path, headers, payload, authorizationHeaderKeys);
        std::string stringToSign = GetStringToSign(canonicalRequest, authorizationHeaderKeys);
        std::string signature = GetSignature(authorizationHeaderKeys, stringToSign);

        std::string authorization = "AWS4-HMAC-SHA256 Credential=" + accessKeyId + "/" + dateString + "/" + region + "/" + module + "/" + requestVersion + ",SignedHeaders=" + signedHeaders + ",Signature=" + signature;
        headers["Authorization"] = authorization;
    }

    bool AwsUtils::VerifySignature(const http::request<http::dynamic_body> &request, const std::string &secretAccessKey) {

        AuthorizationHeaderKeys authorizationHeaderKeys = GetAuthorizationKeys(request, secretAccessKey);

        std::string canonicalRequest = GetCanonicalRequest(request, authorizationHeaderKeys);
        std::string stringToSign = GetStringToSign(canonicalRequest, authorizationHeaderKeys);
        std::string signature = GetSignature(authorizationHeaderKeys, stringToSign);

        if (!Core::StringUtils::Equals(signature, authorizationHeaderKeys.signature)) {
            log_error << "Calculated: " << signature << " provided: " << authorizationHeaderKeys.signature;
            return false;
        }
        return true;
    }

    std::string AwsUtils::GetCanonicalRequest(const http::request<http::dynamic_body> &request, const AuthorizationHeaderKeys &authorizationHeaderKeys) {

        std::stringstream canonicalRequest;
        canonicalRequest << request.method() << '\n';
        canonicalRequest << Core::StringUtils::UrlEncode(request.target()) << '\n';
        canonicalRequest << GetCanonicalQueryParameters(request.target()) << '\n';
        canonicalRequest << GetCanonicalHeaders(request, authorizationHeaderKeys) << '\n';
        canonicalRequest << authorizationHeaderKeys.signedHeaders << '\n';
        canonicalRequest << GetHashedPayload(Core::HttpUtils::GetBodyAsString(request));
        return canonicalRequest.str();
    }

    std::string AwsUtils::GetCanonicalRequest(const std::string &method, const std::string &path, std::map<std::string, std::string> &headers, const std::string &payload, const AuthorizationHeaderKeys &authorizationHeaderKeys) {

        std::stringstream canonicalRequest;
        canonicalRequest << method << '\n';
        canonicalRequest << Core::StringUtils::UrlEncode(path) << '\n';
        canonicalRequest << GetCanonicalQueryParameters(path) << '\n';
        canonicalRequest << GetCanonicalHeaders(headers, authorizationHeaderKeys) << '\n';
        canonicalRequest << authorizationHeaderKeys.signedHeaders << '\n';
        canonicalRequest << GetHashedPayload(payload);
        return canonicalRequest.str();
    }

    std::string AwsUtils::GetStringToSign(const std::string &canonicalRequest, const AuthorizationHeaderKeys &authorizationHeaderKeys) {

        std::stringstream stringToSign;
        stringToSign << authorizationHeaderKeys.signingVersion << '\n';
        stringToSign << authorizationHeaderKeys.isoDateTime << '\n';
        stringToSign << authorizationHeaderKeys.scope << '\n';
        stringToSign << Core::Crypto::GetSha256FromString(canonicalRequest);
        return stringToSign.str();
    }

    std::string AwsUtils::GetCanonicalQueryParameters(const Poco::Net::HTTPRequest &request) {

        std::stringstream canonicalParameters;

        // Get query parameter
        std::map<std::string, std::string> queryParameters = Core::HttpUtils::GetQueryParameters(request.getURI());
        for (const auto &parameter: queryParameters) {
            canonicalParameters << parameter.first << "=" << parameter.second + "&";
        }

        std::string canonicalParameterStr = canonicalParameters.str();

        // Remove last character
        if (Core::StringUtils::Contains(canonicalParameterStr, "&")) {
            canonicalParameterStr.pop_back();
        }
        return canonicalParameterStr;
    }

    std::string AwsUtils::GetCanonicalQueryParameters(const std::string &path) {

        std::stringstream canonicalParameters;

        // Get query parameter
        std::map<std::string, std::string> queryParameters = Core::HttpUtils::GetQueryParameters(path);
        for (const auto &parameter: queryParameters) {
            canonicalParameters << parameter.first << "=" << parameter.second + "&";
        }

        std::string canonicalParameterStr = canonicalParameters.str();

        // Remove last character
        if (Core::StringUtils::Contains(canonicalParameterStr, "&")) {
            canonicalParameterStr.pop_back();
        }
        return canonicalParameterStr;
    }

    std::string AwsUtils::GetCanonicalHeaders(const http::request<http::dynamic_body> &request, const AuthorizationHeaderKeys &authorizationHeaderKeys) {

        std::stringstream canonicalHeaders;

        // Get header
        for (const auto &header: StringUtils::Split(authorizationHeaderKeys.signedHeaders, ';')) {
            if (Core::HttpUtils::HasHeader(request, header)) {
                canonicalHeaders << Poco::toLower(header) << ":" << StringUtils::Trim(Core::HttpUtils::GetHeaderValue(request, header)) + '\n';
            }
        }
        return canonicalHeaders.str();
    }

    std::string AwsUtils::GetCanonicalHeaders(std::map<std::string, std::string> &headers, const AuthorizationHeaderKeys &authorizationHeaderKeys) {

        std::stringstream canonicalHeaders;

        // Get header
        for (const auto &header: StringUtils::Split(authorizationHeaderKeys.signedHeaders, ';')) {
            if (headers.find(header) != headers.end()) {
                canonicalHeaders << Poco::toLower(header) << ":" << StringUtils::Trim(headers[header]) + '\n';
            }
        }
        return canonicalHeaders.str();
    }

    std::string AwsUtils::GetHashedPayload(const std::string &payload) {
        return Core::Crypto::GetSha256FromString(payload);
    }

    AuthorizationHeaderKeys AwsUtils::GetAuthorizationKeys(const http::request<http::dynamic_body> &request, const std::string &secretAccessKey) {

        std::string authorizationHeader = request["Authorization"];

        // Get signing version
        AuthorizationHeaderKeys authKeys;
        authKeys.signingVersion = StringUtils::Split(authorizationHeader, ' ')[0];

        try {
            Poco::RegularExpression::MatchVec posVec;
            Poco::RegularExpression pattern(R"(Credential=([a-zA-Z0-9]+)\/([0-9]{8})\/([a-zA-Z0-9\-]+)\/([a-zA-Z0-9\-]+)\/(aws4_request),\ ?SignedHeaders=(.*),\ ?Signature=(.*)$)");
            if (!pattern.match(authorizationHeader, 0, posVec)) {
                log_error << "Could not extract authorization, authorization: " << authorizationHeader;
                throw Core::UnauthorizedException("Could not extract authorization, authorization: " + authorizationHeader);
            }
            authKeys.secretAccessKey = secretAccessKey.empty() ? "none" : secretAccessKey;
            authKeys.dateTime = authorizationHeader.substr(posVec[2].offset, posVec[2].length);
            authKeys.region = authorizationHeader.substr(posVec[3].offset, posVec[3].length);
            authKeys.module = authorizationHeader.substr(posVec[4].offset, posVec[4].length);
            authKeys.requestVersion = authorizationHeader.substr(posVec[5].offset, posVec[5].length);
            authKeys.signedHeaders = authorizationHeader.substr(posVec[6].offset, posVec[6].length);
            authKeys.signature = authorizationHeader.substr(posVec[7].offset, posVec[7].length);
            authKeys.scope = authKeys.dateTime + "/" + authKeys.region + "/" + authKeys.module + "/" + authKeys.requestVersion;
            authKeys.isoDateTime = Core::HttpUtils::HasHeader(request, "x-amz-date") ? Core::HttpUtils::GetHeaderValue(request, "x-amz-date") : GetISODateString();
            return authKeys;

        } catch (Poco::Exception &e) {
            log_error << e.message();
        }
        return {};
    }

    std::string AwsUtils::GetSignature(const AuthorizationHeaderKeys &authorizationHeaderKeys, const std::string &stringToSign) {
        std::vector<unsigned char> digest = Core::Crypto::GetHmacSha256FromStringRaw("AWS4" + authorizationHeaderKeys.secretAccessKey, authorizationHeaderKeys.dateTime);
        digest = Core::Crypto::GetHmacSha256FromStringRaw(digest, authorizationHeaderKeys.region);
        digest = Core::Crypto::GetHmacSha256FromStringRaw(digest, authorizationHeaderKeys.module);
        digest = Core::Crypto::GetHmacSha256FromStringRaw(digest, authorizationHeaderKeys.requestVersion);
        digest = Core::Crypto::GetHmacSha256FromStringRaw(digest, stringToSign);
        return Core::Crypto::HexEncode(digest.data(), static_cast<int>(digest.size()));
    }

    std::string AwsUtils::GetDateString() {
        auto t = std::time(nullptr);
        auto tm = *std::gmtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y%m%d");
        return oss.str();
    }

    std::string AwsUtils::GetISODateString() {
        auto t = std::time(nullptr);
        auto tm = *std::gmtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%FT%TZ");
        return oss.str();
    }
}// namespace AwsMock::Core
