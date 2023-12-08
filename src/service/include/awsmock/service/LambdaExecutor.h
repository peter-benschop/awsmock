//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDAEXECUTOR_H
#define AWSMOCK_SERVICE_LAMBDAEXECUTOR_H

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Runnable.h>
#include <Poco/Notification.h>
#include <Poco/NotificationQueue.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/MetricServiceTimer.h>
#include <awsmock/dto/lambda/InvocationNotification.h>

namespace AwsMock::Service {

  /**
   * AWS lambda executor. Listens to a Poco notification queue and send the invocation requests sequentially.
   *
   * <p>
   * As the dockerized lambda runtime using AWS RIE only allows the execution of a lambda function at a time, the lambda function invocation will be queued up in a Poco notification queue and executed one by one. Each invocation will wait for the
   * finishing of the last invocation request. The lambda image can run on a remote docker instance. In this case the hostname on the invocation request has to be filled in. Default is 'localhost'.
   * </p>
   *
   * @author jens.vogt@opitz-consulting.com
   */
  class LambdaExecutor : public Poco::Runnable {

  public:

    /**
     * Constructor
     *
     * @param metricService monitoring module
     * @param invokeQueue invoke notification queue
     */
    LambdaExecutor(Core::MetricService &metricService, Poco::NotificationQueue &invokeQueue);

    /**
     * Listens for invocation requests and send the invocation to the right port.
     */
    void run() override;

  private:

    /**
     * Send the invocation request to the corresponding port
     *
     * @param hostName host name of the docker instance
     * @param port lambda docker external port
     * @param body event payload
     */
    void SendInvocationRequest(const std::string &hostName, int port, const std::string &body);

    /**
     * Returns the URI for the invocation request.
     *
     * @param hostName host name of the docker instance
     * @param port lambda docker external port
     * @return URI of the invocation request
     */
    static Poco::URI GetRequestUri(const std::string &hostName, int port);

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Metric module
     */
    Core::MetricService &_metricService;

    /**
     * lambda invocation notification queue
     */
    Poco::NotificationQueue &_invokeQueue;
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_LAMBDAEXECUTOR_H
