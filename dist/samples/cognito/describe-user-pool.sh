#!/bin/bash

# Create a user-pool
aws cognito-idp create-user-pool \
  --pool-name test-user-pool \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock

# List all available
userpoolid=$(aws cognito-idp list-user-pools \
  --max-results 10 \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock | jq -r '.UserPools[0].Id')

# Describe a single user-pool
aws cognito-idp describe-user-pool \
  --user-pool-id $userpoolid \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock
