#!/bin/bash

topicarn=$(aws sns create-topic \
--name test-topic \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.TopicArn')

aws sns publish \
--topic-arn $topicarn \
--message file://./resources/message.json \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

