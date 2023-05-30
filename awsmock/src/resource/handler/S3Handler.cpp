
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
            std::string name = Core::DirUtils::RelativePath(request.getURI());
            if(name.empty()) {
                Dto::S3::ListAllBucketResponse s3Response = _s3Service.ListAllBuckets();

                handleHttpStatusCode(200, response);
                std::ostream &outputStream = response.send();
                outputStream << s3Response.ToXml();
                outputStream.flush();
            }

        } catch (AwsMock::HandlerException &exception) {
            poco_error(_logger, "Server error, exception: " + exception.message());
            handleHttpStatusCode(exception.code(), response);
            std::ostream &outputStream = response.send();
            outputStream << toJson(exception);
        } catch (Core::ResourceNotFoundException &exception) {
            poco_error(_logger, "Server error, exception: " + exception.displayText());
            handleHttpStatusCode(500, response);
            std::ostream &outputStream = response.send();
            outputStream << toJson(exception);
        }
    }

    void S3Handler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_PUT_TIMER);
        poco_debug(_logger, "S3 PUT request, URI: " + request.getURI() + " region: " + region + " user: " + user);

        try {
            bool isMultipartUpload = QueryParameterExists("uploadId");

            if(isMultipartUpload) {

                std::string partNumber = GetQueryParameter("partNumber", false);
                std::string uploadId = GetQueryParameter("uploadId", false);
                poco_debug(_logger, "S3 Multipart upload part: " + partNumber);

                std::string eTag = _s3Service.UploadPart(request.stream(), std::stoi(partNumber), uploadId);

                Poco::DateTime now;
                response.set("ETag", eTag);
                response.set("Date", Poco::DateTimeFormatter::format(now, Poco::DateTimeFormat::HTTP_FORMAT));
                response.set("Content-Length", "0");
                response.set("Connection", "keep-alive");
                response.set("Server", "AmazonS3");

                handleHttpStatusCode(200, response);
                std::ostream &outputStream = response.send();
                outputStream.flush();

            } else {

                std::string name = Core::DirUtils::RelativePath(request.getURI());
                std::string payload = GetPayload(request);
                Dto::S3::CreateBucketRequest s3Request(payload);
                Dto::S3::CreateBucketResponse s3Response = _s3Service.CreateBucket(name, user, s3Request);

                handleHttpStatusCode(200, response);
                response.set("Location", s3Response.GetLocation());
                std::ostream &outputStream = response.send();
                outputStream << s3Response.ToXml();
                outputStream.flush();
            }

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Exception: " + exc.message());
            handleHttpStatusCode(exc.code(), response);
            std::ostream &outputStream = response.send();
            //outputStream << toJson(exc);
            outputStream.flush();
        }
    }

    void S3Handler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_POST_TIMER);
        poco_debug(_logger, "S3 POST request, URI: " + request.getURI() + " region: " + region + " user: " + user);

        try {

            std::string bucket = GetBucketFromUri(request.getURI());
            std::string key = GetKeyFromUri(request.getURI());
            bool isMultipartUpload = QueryParameterExists("uploads");

            if(isMultipartUpload) {

                poco_debug(_logger, "Starting multipart upload");

                Poco::DateTime now;
                response.set("Date", Poco::DateTimeFormatter::format(now, Poco::DateTimeFormat::HTTP_FORMAT));
                response.set("Transfer-Encoding", "chunked");
                response.set("Connection", "keep-alive");
                response.set("Server", "AmazonS3");

                Dto::S3::InitiateMultipartUploadResult result = _s3Service.CreateMultipartUpload(bucket, key, region, user);
                handleHttpStatusCode(200, response);
                std::ostream &outputStream = response.send();
                outputStream << result.ToXml();
                outputStream.flush();

            } else {

                std::string uploadId = GetQueryParameter("uploadId", true);
                poco_debug(_logger, "Finish multipart upload request, uploadId: " + uploadId);

                Dto::S3::CompleteMultipartUploadResult result = _s3Service.CompleteMultipartUpload(uploadId, bucket, key, region, user);
                handleHttpStatusCode(200, response);
                std::ostream &outputStream = response.send();
                outputStream << result.ToXml();
                outputStream.flush();

            }

        } catch (Poco::Exception &exc) {

            poco_error(_logger, "Exception: " + exc.message());
            handleHttpStatusCode(exc.code(), response);
            std::ostream &outputStream = response.send();
            //outputStream << toJson(exception);
            outputStream.flush();
        }
    }

    void S3Handler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        try {
            Core::MetricServiceTimer measure(_metricService, HTTP_DELETE_TIMER);
            poco_debug(_logger, "S3 DELETE request, URI: " + request.getURI() + " region: " + region + " user: " + user);

            try {
                const std::string &name = Core::DirUtils::RelativePath(request.getURI());
                _s3Service.DeleteBucket(region, name);

                handleHttpStatusCode(200, response);
                std::ostream &outputStream = response.send();
                outputStream.flush();

            } catch (HandlerException &exception) {
                handleHttpStatusCode(exception.code(), response);
                std::ostream &outputStream = response.send();
                //outputStream << toJson(exception);
                outputStream.flush();
            }
        }catch(Poco::Exception &ex) {
            poco_error(_logger, "Exception: " + ex.message());
        }
    }

    void S3Handler::handleOptions(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
        Core::MetricServiceTimer measure(_metricService, HTTP_OPTIONS_TIMER);
        poco_debug(_logger, "S3 OPTIONS request, address: " + request.clientAddress().toString());

        response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(200, response);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }

    std::string S3Handler::GetPayload(Poco::Net::HTTPServerRequest &request) {
        std::string payload;
        std::istream &inputStream = request.stream();
        Poco::StreamCopier::copyToString(inputStream, payload);
        poco_trace(_logger, "S3 Payload: " + payload);
        return payload;
    }

    std::string S3Handler::GetBucketFromUri(const std::string &uri) {
        return Core::StringUtils::SubString(uri, 1, uri.find_first_of('/', 1) - 1);
    }

    std::string S3Handler::GetKeyFromUri(const std::string &uri) {
        return Core::StringUtils::SubString(uri, uri.find_first_of('/', 1) + 1, uri.find_first_of('?') - 1);
    }
}
