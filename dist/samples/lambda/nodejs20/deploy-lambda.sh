#!/bin/bash

# Create bucket
aws s3 mb s3://test-bucket \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock

# Create lambda function
aws lambda create-function \
  --function-name nodejs-events \
  --runtime nodejs20.x \
  --timeout 120 \
  --memory-size 2024 \
  --tags tag=latest,version=latest \
  --environment file://./resources/nodejs-lambda-env.json \
  --ephemeral-storage Size=2024 \
  --handler index.handler \
  --zip-file fileb://./resources/nodejs-events.zip \
  --role arn:aws:iam::000000000000:role/lambda-role \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock
