#!/bin/bash

# Create a user-pool
userpoolid=$(aws cognito-idp create-user-pool \
  --pool-name test-user-pool \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock | jq -r '.UserPool.Id')

aws cognito-idp create-user-pool-client \
  --user-pool-id $userpoolid \
  --client-name test-client \
  --generate-secret \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock

