#!/bin/bash

# List all available user pools
aws cognito-idp list-user-pools \
  --max-result 10 \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock
