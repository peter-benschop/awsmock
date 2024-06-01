#!/bin/bash

alias awslocal="aws --region eu-central-1 --endpoint --endpoint http://localhost:4566 --profile awsmock"

# Delete function
awslocal lambda delete-function \
  --function-name java-events

# Remove objects
awslocal s3 rm s3://test-bucket \
  --recursive

# Remove bucket
awslocal s3 rb s3://test-bucket
