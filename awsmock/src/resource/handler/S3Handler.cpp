
#include "awsmock/resource/handler/S3Handler.h"

namespace AwsMock {

    S3Handler::S3Handler(Core::Configuration &configuration, Core::MetricService &metricService)
        : AbstractResource(), _logger(Poco::Logger::get("S3Handler")), _configuration(configuration), _metricService(metricService), _s3Service(configuration) {
        Core::Logger::SetDefaultConsoleLogger("S3Handler");
    }

    void S3Handler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_GET_TIMER);
        poco_debug(_logger, "S3 GET request, URI: " + request.getURI() + " region: " + region + " user: " + user);

        try {

            std::string bucket, key;
            GetBucketKeyFromUri(request.getURI(), bucket, key);

            bool isListRequest = QueryParameterExists("list-type");

            if(bucket.empty()) {

                // Return bucket list
                Dto::S3::ListAllBucketResponse s3Response = _s3Service.ListAllBuckets();
                SendOkResponse(response, s3Response.ToXml());

            } else if(!bucket.empty() && !key.empty()) {

                // Get object request
                poco_debug(_logger, "S3 get object request, bucket: " + bucket + " key: " + key);
                Dto::S3::GetObjectRequest s3Request;
                s3Request.SetBucket(bucket);
                s3Request.SetKey(key);

                Dto::S3::GetObjectResponse s3Response = _s3Service.GetObject(s3Request);
                std::ifstream ifs (s3Response.GetFilename());

                Resource::HeaderMap headerMap;
                headerMap.emplace_back("ETag", Core::StringUtils::GenerateRandomString(32));
                headerMap.emplace_back("Content-Type", s3Response.GetContentType());
                headerMap.emplace_back("Content-Length", std::to_string(s3Response.GetSize()));
                headerMap.emplace_back("Last-Modified", s3Response.GetLastModified());

                SendOkResponse(response, s3Response.GetFilename(), s3Response.GetSize(), &headerMap);

            } else if(isListRequest) {

                // Return object list
                Dto::S3::ListBucketResult result = _s3Service.ListBucket(bucket);
                SendOkResponse(response, result.ToXml());
            }

        } catch (Core::ServiceException &exc) {
            SendErrorResponse("S3", response, exc);
        } catch (Core::ResourceNotFoundException &exc) {
            SendErrorResponse("S3", response, exc);
        }
    }

    void S3Handler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_PUT_TIMER);
        poco_debug(_logger, "S3 PUT request, URI: " + request.getURI() + " region: " + region + " user: " + user);

        try {

            std::string bucket, key;
            GetBucketKeyFromUri(request.getURI(), bucket, key);
            poco_debug(_logger, "S3 put request, bucket: " + bucket + " key: " + key);

            bool isMultipartUpload = QueryParameterExists("uploadId");
            bool isNotification = QueryParameterExists("notification");

            if (isMultipartUpload) {

                // S3 initial multipart upload
                std::string partNumber = GetQueryParameter("partNumber", false);
                std::string uploadId = GetQueryParameter("uploadId", false);
                poco_debug(_logger, "Initial S3 multipart upload part: " + partNumber);

                std::string eTag = _s3Service.UploadPart(request.stream(), std::stoi(partNumber), uploadId);

                Resource::HeaderMap headerMap;
                headerMap.emplace_back("ETag", eTag);

                SendOkResponse(response, {}, &headerMap);

            } else if(isNotification) {

                poco_debug(_logger, "Bucket notification request, bucket: " + bucket);

                // S3 notification setup
                Dto::S3::PutBucketNotificationRequest s3Request = Dto::S3::PutBucketNotificationRequest(GetPayload(request), region, bucket);

                _s3Service.PutBucketNotification(s3Request);

                SendOkResponse(response);

            } else if(!key.empty()) {

                // S3 put object request
                Dto::S3::PutObjectRequest putObjectRequest;

                putObjectRequest.bucket = bucket;
                putObjectRequest.key = key;
                putObjectRequest.owner = user;
                putObjectRequest.region = region;
                putObjectRequest.contentType = request.get("Content-Type");
                putObjectRequest.md5Sum = request.get("Content-MD5");
                putObjectRequest.size = std::stol(request.get("Content-Length"));

                Dto::S3::PutObjectResponse putObjectResponse = _s3Service.PutObject(putObjectRequest, &request.stream());

                Resource::HeaderMap headerMap;
                headerMap.emplace_back("ETag", putObjectResponse.etag);

                SendOkResponse(response, {}, &headerMap);

            } else if(!bucket.empty()){

                // S3 create bucket request
                std::string name = Core::DirUtils::RelativePath(request.getURI());
                std::string payload = GetPayload(request);
                Dto::S3::CreateBucketRequest s3Request(payload);
                Dto::S3::CreateBucketResponse s3Response = _s3Service.CreateBucket(name, user, s3Request);

                SendOkResponse(response, s3Response.ToXml());

            }

        } catch (Poco::Exception &exc) {
            SendErrorResponse("S3", response, exc);
        }
    }

    void S3Handler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_POST_TIMER);
        poco_debug(_logger, "S3 POST request, URI: " + request.getURI() + " region: " + region + " user: " + user);

        try {

            std::string bucket, key;
            GetBucketKeyFromUri(request.getURI(), bucket, key);

            bool isMultipartUpload = QueryParameterExists("uploads");
            bool isDeleteObjects = QueryParameterExists("delete");

            if (isMultipartUpload) {

                poco_debug(_logger, "Starting multipart upload");

                Dto::S3::InitiateMultipartUploadResult result = _s3Service.CreateMultipartUpload(bucket, key, region, user);
                SendOkResponse(response, result.ToXml());

            } else if(isDeleteObjects) {

                poco_debug(_logger, "Starting delete objects request");

                std::string payload = GetPayload(request);

                auto s3Request = Dto::S3::DeleteObjectsRequest(payload);
                Dto::S3::DeleteObjectsResponse s3Response = _s3Service.DeleteObjects(s3Request);
                SendOkResponse(response, s3Response.ToXml());

            } else {

                std::string uploadId = GetQueryParameter("uploadId", true);
                poco_debug(_logger, "Finish multipart upload request, uploadId: " + uploadId);

                Dto::S3::CompleteMultipartUploadResult result = _s3Service.CompleteMultipartUpload(uploadId, bucket, key, region, user);
                SendOkResponse(response, result.ToXml());

            }

        } catch (Poco::Exception &exc) {
            SendErrorResponse("S3", response, exc);
        }
    }

    void S3Handler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_DELETE_TIMER);
        poco_debug(_logger, "S3 DELETE request, URI: " + request.getURI() + " region: " + region + " user: " + user);

        try {
            std::string bucket, key;
            GetBucketKeyFromUri(request.getURI(), bucket, key);

            if(!bucket.empty() && !key.empty()) {
                _s3Service.DeleteObject({.region=region, .bucket=bucket, .key=key});
                SendDeleteResponse(response);
            } else if(!bucket.empty()) {
                _s3Service.DeleteBucket(region, bucket);
                SendDeleteResponse(response);
            }

        } catch (Core::ServiceException &exc) {
            SendErrorResponse("S3", response, exc);
        }
    }

    void S3Handler::handleOptions(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
        Core::MetricServiceTimer measure(_metricService, HTTP_OPTIONS_TIMER);
        poco_debug(_logger, "S3 OPTIONS request, address: " + request.clientAddress().toString());

        response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(response, 200);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }

    void S3Handler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
        Core::MetricServiceTimer measure(_metricService, HTTP_HEAD_TIMER);
        poco_debug(_logger, "S3 HEAD request, address: " + request.clientAddress().toString());

        try {

            std::string bucket, key;
            GetBucketKeyFromUri(request.getURI(), bucket, key);
            poco_debug(_logger, "S3 HEAD request, bucket: " + bucket + " key: " + key);

            Dto::S3::GetMetadataRequest s3Request;
            s3Request.SetBucket(bucket);
            s3Request.SetKey(key);
            Dto::S3::GetMetadataResponse s3Response = _s3Service.GetMetadata(s3Request);

            Resource::HeaderMap headerMap;
            headerMap.emplace_back("Last-Modified", s3Response.GetLastModified());
            headerMap.emplace_back("Content-Length", std::to_string(s3Response.GetSize()));
            headerMap.emplace_back("Content-Type", s3Response.GetContentType());
            headerMap.emplace_back("Connection", "closed");
            headerMap.emplace_back("Server", "AmazonS3");

            SendOkResponse(response, {}, &headerMap);


        } catch (Poco::Exception &exc) {
            SendErrorResponse("S3", response, exc);
        }
    }

    void S3Handler::GetBucketKeyFromUri(const std::string &uri, std::string &bucket, std::string &key) {

        Poco::RegularExpression::MatchVec posVec;
        Poco::RegularExpression pattern(R"(/([a-z0-9-.]+)?/?([a-zA-Z0-9-_/.*'()]+)?\??.*$)");
        if (!pattern.match(uri, 0, posVec)) {
            throw Core::ResourceNotFoundException("Could not extract bucket and key");
        }

        if (posVec.size() > 1) {
            bucket = uri.substr(posVec[1].offset, posVec[1].length);
        }
        if (posVec.size() > 2) {
            key = uri.substr(posVec[2].offset, posVec[2].length);
        }
    }
}
