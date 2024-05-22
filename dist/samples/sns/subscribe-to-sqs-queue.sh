#!/bin/bash

# Create topic
topicarn=$(aws sns create-topic \
--name test-topic \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.TopicArn')

# Create SQS queue
queueurl=$(aws sqs create-queue \
--queue-name test-queue \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.QueueUrl')

# Create subscription
aws sns subscribe \
--topic-arn $topicarn \
--protocol sqs \
--notification-endpoint $queueurl \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

# Send message
aws sns publish \
--topic-arn $topicarn \
--message file://./resources/message.json \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

# See if message arrived in SQS
numberOfMessages=$(aws sqs get-queue-attributes \
--queue-url $queueurl \
--attribute-names ALL \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.Attributes.ApproximateNumberOfMessages')

echo "Number of messages: $numberOfMessages"
