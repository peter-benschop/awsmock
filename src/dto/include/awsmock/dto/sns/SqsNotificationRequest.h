//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_SQSNOTIFICAITONREQUEST_H
#define AWSMOCK_DTO_SNS_SQSNOTIFICAITONREQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Timestamp.h>

// AwsMock includes
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::SNS {

    /**
   * SQS notification request, used to send a notification from an SNS topic to a SQS queue
   *
   * <p>
   * Example:
   * {
   *   "Type" : "Notification",
   *   "MessageId" : "467f295c-b4fe-5e24-a627-74c9652562a8",
   *   "TopicArn" : "arn:aws:sns:eu-central-1:012096702153:pim-prod-protokollierung-topic",
   *   "Message" : "{\"protokollMeldung\":{\"verarbeitungsschritt\":\"KATALOGDATENDB\",\"dateiverarbeitungStatus\":\"ERFOLGREICH\",\"isKlaerfall\":false,\"isDatenlieferantFeedback\":false},\"anlieferungsContext\":{\"datenlieferantId\":\"DLI385\",\"anlieferungsdatum\":\"2023-10-02T18:15:02.9\",\"filePathOriginaldatei\":\"DLI385/ACdelta23267_02102023181502925.xml\",\"produktId\":\"082106559\"}}",
   *   "Timestamp" : "2023-10-03T08:23:55.183Z",
   *   "SignatureVersion" : "1",
   *   "Signature" : "OI5myFtSfUP8dOymRI0cW48FTAmb/VHYI2N10DwQ7X/fkHtJmG7hJNC4qjOkYUYC6kTATshpvo/VR5v0nnIHBFYgxrb9diLUMG2AsI6z2F02nGGWSTOjnH0XFpCGdyOB+2En6EZhzoUTOdFpGRXsijFDmXfxt2vS/RaGJLz/6Ibz+KeEYosgElQ2R1Nr9lz8jHCeaSdPzW7rTyIXv0b+cBDd8xHFc79IkSGmuepidAseTKkLX+oZ5Ry3Q1iTtTMOziXoz6kZhXXZHy/Q/clYCMzTP7BabDG5LK11gNfA0ytO/KDyiWxGykUommXnk6rt7FcCnNDW5/qrAmPHzbaO3w==",
   *   "SigningCertURL" : "https://sns.eu-central-1.amazonaws.com/SimpleNotificationService-01d088a6f77103d0fe307c0069e40ed6.pem",
   *   "UnsubscribeURL" : "https://sns.eu-central-1.amazonaws.com/?Action=Unsubscribe&SubscriptionArn=arn:aws:sns:eu-central-1:012096702153:pim-prod-protokollierung-topic:a278c03b-c5de-42a4-9c0e-f9c3412de940"
   * }
   */
    struct SqsNotificationRequest {

        /**
     * Notification type
     */
        std::string type = "Notification";

        /**
     * Message ID
     */
        std::string messageId;

        /**
     * Source SNS topic ARN
     */
        std::string topicArn;

        /**
     * SQS message body
     */
        std::string message;

        /**
     * Send time stamp
     */
        long timestamp;

        /**
     * Signature
     */
        std::string signature;

        /**
     * Signature version
     */
        std::string signatureVersion = "1";

        /**
     * Signing CERT URL
     */
        std::string signingCertURL;

        /**
     * Unsubscribe URL
     */
        std::string unsubscribeURL;

        /**
     * Converts the DTO to a JSON representation.
     *
     * @return DTO as JSON string.
     */
        [[nodiscard]] std::string ToJson() const;

        /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
        [[nodiscard]] std::string ToString() const;

        /**
     * Stream provider.
     *
     * @return output stream
     */
        friend std::ostream &operator<<(std::ostream &os, const SqsNotificationRequest &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_SQSNOTIFICAITONREQUEST_H
