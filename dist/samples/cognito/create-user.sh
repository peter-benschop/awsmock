#!/bin/bash

# Create a single user-pool
userpoolid=$(aws cognito-idp create-user-pool \
  --pool-name test-user-pool \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock | jq -r '.UserPool.Id')

# Create user in user pool
aws cognito-idp admin-create-user \
  --user-pool-id $userpoolid \
  --username test-user \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock
