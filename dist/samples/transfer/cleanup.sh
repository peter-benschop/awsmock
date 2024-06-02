#!/bin/bash

alias awslocal="aws --region eu-central-1 --endpoint --endpoint http://localhost:4566 --profile awsmock"

# Look for server ID
serverId=$(awslocal transfer list-servers | jq -r '.Servers[0].ServerId')

# Delete server
awslocal transfer delete-server \
  --server-id $serverId

