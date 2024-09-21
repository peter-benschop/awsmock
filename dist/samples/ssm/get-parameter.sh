#!/bin/bash

# Create simple symmetric key (AES256)
aws ssm put-parameter \
--name test-name \
--value test-value \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

aws ssm get-parameter \
--name test-name \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.Parameter.Name'

aws ssm delete-parameter \
--name test-name \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.Parameters[].Name'

