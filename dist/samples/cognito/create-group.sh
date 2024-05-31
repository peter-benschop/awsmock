#!/bin/bash

# Create a single user-pool
userpoolid=$(aws cognito-idp create-user-pool \
  --pool-name test-user-pool \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock | jq -r '.UserPool.Id')

# Create group
aws cognito-idp create-group \
  --user-pool-id $userpoolid \
  --group-name test-group \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock
