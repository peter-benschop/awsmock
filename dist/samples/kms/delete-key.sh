#!/bin/bash

# Create simple symmetric key (AES256)
keyid=$(aws kms create-key \
--key-usage ENCRYPT_DECRYPT \
--key-spec SYMMETRIC_DEFAULT \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.KeyMetadata.KeyId')

# Delete the key
aws kms schedule-key-deletion \
--key-id $keyid \
--pending-window-in-days 1 \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

# Describe key
aws kms describe-key \
--key-id $keyid \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock
