#!/bin/bash

# Create simple symmetric key (AES256)
aws kms list-keys \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

