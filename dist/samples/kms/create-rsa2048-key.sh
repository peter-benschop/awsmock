#!/bin/bash

# Create simple symmetric key (AES256)
aws kms create-key \
--key-usage ENCRYPT_DECRYPT \
--key-spec RSA_2048 \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

