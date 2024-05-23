#!/bin/bash

# Invoke function
aws lambda invoke \
  --function-name java-events \
  --payload fileb://./resources/s3-notification.json \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock \
  out.json
