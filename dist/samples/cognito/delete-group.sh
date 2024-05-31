#!/bin/bash

# Create a user-pool
userpoolid=$(aws cognito-idp create-user-pool \
  --pool-name test-user-pool \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock | jq -r '.UserPool.Id')

# Create group
groupname=$(aws cognito-idp create-group \
  --user-pool-id $userpoolid \
  --group-name test-group \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock | jq -r '.Group.GroupName')

# List all available
aws cognito-idp list-groups \
  --user-pool-id $userpoolid \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock

# Delete a single user-pool
aws cognito-idp delete-group \
  --user-pool-id $userpoolid \
  --group-name $groupname \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock

# List all available
aws cognito-idp list-groups \
  --user-pool-id $userpoolid \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock
