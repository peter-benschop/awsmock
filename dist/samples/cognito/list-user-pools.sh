#!/bin/bash

alias awslocal="aws --region eu-central-1 --endpoint --endpoint http://localhost:4566 --profile awsmock"

# List all available user pools
awslocal cognito-idp list-user-pools --max-result 10
