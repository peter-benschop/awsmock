#!/bin/bash

# Create queue
queueurl=$(aws sqs create-queue \
--queue-name test-queue \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.QueueUrl')

# Delete topic
aws sqs delete-queue \
--queue-url $queueurl \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

# List queues
aws sqs list-queues \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | grep $queueurl

