//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_SQS_CMD_HANDLER_H
#define AWSMOCK_SERVICE_SQS_CMD_HANDLER_H

// Poco includes
#include <Poco/Condition.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/dto/common/SQSClientCommand.h>
#include <awsmock/dto/sqs/DeleteMessageBatchEntry.h>
#include <awsmock/dto/sqs/DeleteMessageBatchRequest.h>
#include <awsmock/dto/sqs/GetQueueUrlRequest.h>
#include <awsmock/dto/sqs/GetQueueUrlResponse.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/sqs/SQSService.h>

#define DEFAULT_SQS_ACCOUNT_ID "000000000000"

namespace AwsMock::Service {

    /**
     * SQS command handler  list
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    typedef std::map<std::string, std::string> AttributeList;

    /**
     * AWS SQS mock handler.
     *
     * <p>The SQS request are coming in two different flavours. Using the AWS CLI the queue URL is part of the HTTP parameters in the body of the message. Both are
     * using POST request, whereas the Java SDK is providing the queue-url as part of the HTTP URL in the header of the request.</p>
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SQSCmdHandler : public virtual AbstractHandler {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit SQSCmdHandler(Core::Configuration &configuration) : AbstractHandler(), _configuration(configuration), _sqsService(configuration) {}

      protected:

        /**
         * HTTP POST request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param sqsClientCommand standardised client command
         * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::SQSClientCommand &sqsClientCommand);

      private:

        /**
         * Get the queue userAttributes.
         *
         * @param payload HTTP body
         * @return list of queue userAttributes
         */
        static std::vector<Dto::SQS::QueueAttribute> GetQueueAttributes(const std::string &payload);

        /**
         * Get the queue tags.
         *
         * @param payload HTTP body
         * @return list of queue tags
         */
        static std::map<std::string, std::string> GetQueueTags(const std::string &payload);

        /**
         * Get the queue attribute names.
         *
         * @param payload HTTP body
         * @return list of queue attribute names
         */
        static std::vector<std::string> GetQueueAttributeNames(const std::string &payload);

        /**
         * Get the message attributes.
         *
         * @param payload HTTP body
         * @return list of message userAttributes
         */
        static std::map<std::string, Dto::SQS::MessageAttribute> GetMessageAttributes(const std::string &payload);

        /**
         * Converts the attributes and message attributes into HTTP headers for the receive message request
         *
         * @param response HTTP response
         * @param sqsResponse Receive message response from SQS service
         * @return
         */
        static std::map<std::string, std::string> AddReceiveHeaders(Poco::Net::HTTPResponse &response, const Dto::SQS::ReceiveMessageResponse &sqsResponse);

        /**
         * ImageHandler import configuration
         */
        Core::Configuration &_configuration;

        /**
         * SQS module
         */
        Service::SQSService _sqsService;

        /**
         * Default account ID
         */
        std::string _accountId;

        /**
         * Default endpoint
         */
        std::string _endpoint;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SQS_CMD_HANDLER_H
