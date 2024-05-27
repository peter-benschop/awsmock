#!/bin/bash

# Create a single user-pool
userpoolid=$(aws cognito-idp create-user-pool \
  --pool-name test-user-pool \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock | jq -r '.UserPool.Id')

# Create a single user-pool domain
aws cognito-idp create-user-pool-domain \
  --domain test-domain \
  --user-pool-id $userpoolid \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock
