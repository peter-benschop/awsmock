#!/bin/bash

alias awslocal="aws --region eu-central-1 --endpoint --endpoint http://localhost:4566 --profile awsmock"

# Create a user-pool
awslocal cognito-idp create-user-pool --pool-name test-user-pool

# List all available
userPoolId=$(awslocal cognito-idp list-user-pools --max-results 10 | jq -r '.UserPools[0].Id')

# Describe a user-pool
awslocal cognito-idp describe-user-pool --user-pool-id $userPoolId