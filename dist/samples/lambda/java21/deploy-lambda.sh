#!/bin/bash

# Create bucket
#aws s3 mb s3://test-bucket \
#  --region eu-central-1 \
#  --endpoint http://localhost:4566 \
#  --profile awsmock

# Copy image to bucket
#aws s3 cp ./resources/sample-java-events.png s3://test-bucket/inbound/sample-java-s3.png \
#  --region eu-central-1 \
#  --endpoint http://localhost:4566 \
#  --profile awsmock

# Create lambda function
aws lambda create-function \
  --function-name java-events \
  --runtime Java21 \
  --timeout 120 \
  --memory-size 2024 \
  --tags tag=latest,version=latest \
  --ephemeral-storage Size=2024 \
  --handler example.HandlerS3 \
  --region eu-central-1 \
  --zip-file fileb://./resources/java-events-1.0-SNAPSHOT.jar \
  --role arn:aws:iam::000000000000:role/lambda-role \
  --cli-read-timeout 0 \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock
