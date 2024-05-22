#!/bin/bash

# Create topic
topicarn=$(aws sns create-topic \
--name test-topic \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.TopicArn')

# Delete topic
aws sns delete-topic \
--topic-arn $topicarn \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock


