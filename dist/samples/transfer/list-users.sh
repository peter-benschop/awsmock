#!/bin/bash

alias awslocal="aws --region eu-central-1 --endpoint --endpoint http://localhost:4566 --profile awsmock"

# Create transfer server
serverId=$(awslocal transfer create-server \
  --protocols ftp | jq -r '.ServerId')

# Create user
userId=ftpuser1
role="arn:aws:iam::000000000000:role/$userId"
awslocal transfer create-user \
  --server-id $serverId \
  --role $role \
  --user-name $userId \
  --home-directory $userId

# List users
awslocal transfer list-users \
  --server-id $serverId
