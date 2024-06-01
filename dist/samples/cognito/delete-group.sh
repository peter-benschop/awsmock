#!/bin/bash

alias awslocal="aws --region eu-central-1 --endpoint --endpoint http://localhost:4566 --profile awsmock"

# Create a user-pool
userPoolId=$(awslocal cognito-idp create-user-pool --pool-name test-user-pool | jq -r '.UserPool.Id')

# Create group
groupname=$(awslocal cognito-idp create-group --user-pool-id $userPoolId --group-name test-group | jq -r '.Group.GroupName')

# List all available groups
awslocal cognito-idp list-groups --user-pool-id $userPoolId

# Delete the group
awslocal cognito-idp delete-group --user-pool-id $userPoolId --group-name $groupname

# List all available groups
awslocal cognito-idp list-groups --user-pool-id $userPoolId