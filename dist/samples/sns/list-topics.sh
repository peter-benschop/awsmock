#!/bin/bash

# Create topic
aws sns create-topic \
--name test-topic \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

# list topics
aws sns list-topics \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

