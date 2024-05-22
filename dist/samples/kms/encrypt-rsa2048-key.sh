#!/bin/bash

# Create simple symmetric key (AES256)
keyid=$(aws kms create-key \
--key-usage ENCRYPT_DECRYPT \
--key-spec RSA_2048 \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.KeyMetadata.KeyId')

# Base64 encoding
base64_plaintext=$(base64 ./resources/plaintext.txt)

# Encrypt test file
aws kms encrypt \
--key-id $keyid \
--plaintext $base64_plaintext \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.CiphertextBlob' > ./resources/ciphertext.b64

# Decrypt test file
aws kms decrypt \
--key-id $keyid \
--ciphertext-blob file://./resources/ciphertext.b64 \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock | jq -r '.Plaintext' | base64 -d
 printf '\n'

 # Cleanup
 rm -f ./resources/ciphertext.b64
