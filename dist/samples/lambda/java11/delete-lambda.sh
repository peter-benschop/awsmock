#!/bin/bash

# Delete function
aws lambda delete-function \
  --function-name java-events \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock

# Remove objects
aws s3 rm s3://test-bucket \
  --recursive \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock

# Remove bucket
aws s3 rb s3://test-bucket \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock
