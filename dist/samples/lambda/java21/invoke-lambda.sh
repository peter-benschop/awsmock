#!/bin/bash

alias awslocal="aws --region eu-central-1 --endpoint --endpoint http://localhost:4566 --profile awsmock"

# Invoke function
awslocal lambda invoke \
  --function-name java-events \
  --payload fileb://./resources/s3-notification.json \
  out.json
