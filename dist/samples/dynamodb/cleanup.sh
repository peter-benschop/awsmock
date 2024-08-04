#!/bin/bash

alias awslocal="aws --region eu-central-1 --endpoint --endpoint http://localhost:4566 --profile awsmock"

# Delete the table
awslocal dynamodb delete-table \
  --table-name MusicCollection