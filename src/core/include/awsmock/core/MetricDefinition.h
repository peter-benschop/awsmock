//
// Created by vogje01 on 26/08/2022.
//

#ifndef AWSMOCK_CORE_METRIC_DEFINITION_H
#define AWSMOCK_CORE_METRIC_DEFINITION_H

// HTTP timer
#define GATEWAY_GET_TIMER "gateway_get_time"
#define GATEWAY_PUT_TIMER "gateway_put_time"
#define GATEWAY_POST_TIMER "gateway_post_time"
#define GATEWAY_DELETE_TIMER "gateway_delete_time"
#define GATEWAY_OPTIONS_TIMER "gateway_options_time"
#define GATEWAY_HEAD_TIMER "gateway_head_time"

#define GATEWAY_COUNTER "gateway_count"

#define MODULE_GET_TIMER "manager_get_time"
#define MODULE_PUT_TIMER "manager_put_time"
#define MODULE_POST_TIMER "manager_post_time"
#define MODULE_DELETE_TIMER "manager_delete_time"
#define MODULE_OPTIONS_TIMER "manager_options_time"
#define MODULE_HEAD_TIMER "manager_head_time"

#define MODULE_COUNTER "manager_count"

#define SNS_TOPIC_COUNT "sns_topic_count_total"
#define SNS_MESSAGE_COUNT "sns_topic_count_total"
#define SNS_MESSAGE_BY_TOPIC_COUNT "sns_message_by_topic_count"

#define SQS_QUEUE_COUNT "sqs_queue_count_total"
#define SQS_MESSAGE_COUNT "sqs_message_count_total"
#define SQS_MESSAGE_BY_QUEUE_COUNT "sqs_message_by_queue_count"

#define S3_BUCKET_COUNT "s3_bucket_count_total"
#define S3_OBJECT_COUNT "s3_object_count_total"
#define S3_OBJECT_BY_BUCKET_COUNT "s3_object_by_bucket_count"

#define LAMBDA_FUNCTION_COUNT "lambda_function_count_total"

#define DYNAMODB_TABLE_COUNT "dynamodb_table_count_total"

#endif  // AWSMOCK_CORE_METRIC_DEFINITION_H
