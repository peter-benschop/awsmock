#!/bin/bash

# Create queue
queueurl=$(aws sqs create-queue \
--queue-name test-queue \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.QueueUrl')

# Send message
aws sqs send-message \
--queue-url $queueurl \
--message-body file://./resources/message.json \
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
