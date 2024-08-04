#!/bin/bash

alias awslocal="aws --region eu-central-1 --endpoint --endpoint http://localhost:4566 --profile awsmock"

# Create bucket
awslocal s3 mb s3://test-bucket

# Copy image to bucket
awslocal s3 cp ./resources/sample-java-events.png s3://test-bucket/inbound/sample-java-s3.png

# Create lambda function
awslocal lambda create-function \
  --function-name java-events \
  --runtime java21 \
  --timeout 120 \
  --memory-size 2024 \
  --tags tag=latest,version=latest \
  --ephemeral-storage Size=2024 \
  --handler example.HandlerS3 \
  --region eu-central-1 \
  --zip-file fileb://./resources/java-events-1.0-SNAPSHOT.jar \
  --role arn:aws:iam::000000000000:role/lambda-role \
  --cli-read-timeout 0