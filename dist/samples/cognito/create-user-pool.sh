#!/bin/bash

alias awslocal="aws --region eu-central-1 --endpoint --endpoint http://localhost:4566 --profile awsmock"

# Create a user-pool
awslocal cognito-idp create-user-pool --pool-name test-user-pool
