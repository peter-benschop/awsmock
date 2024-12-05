#!/bin/bash

alias awslocal="aws --region eu-central-1 --endpoint --endpoint http://localhost:4566 --profile awsmock"

# Create a table
awslocal dynamodb create-table \
  --table-name MusicCollection \
  --attribute-definitions file://./resources/attributes.json \
  --key-schema file://./resources/key-schema.json \
  --provisioned-throughput file://./resources/capacity.json \
  --tags file://./resources/tags.json \

# Create a table
awslocal dynamodb describe-table \
  --table-name MusicCollection

