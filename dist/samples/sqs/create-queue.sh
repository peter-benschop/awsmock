#!/bin/bash

aws sqs create-queue \
--queue-name test-queue \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

