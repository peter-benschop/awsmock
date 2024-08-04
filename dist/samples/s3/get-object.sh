#!/bin/bash

# Create temp files
tmpfile=$(mktemp -p /tmp).txt
base64 /dev/urandom | head -c 1k > $tmpfile
tmpfile=$(basename $tmpfile)

# Copy to S3 bucket
aws s3 cp /tmp/$tmpfile s3://test-bucket/$tmpfile \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

# Copy to local file
aws s3 cp s3://test-bucket/$tmpfile ./tmp.txt \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

# Cleanup
rm -f /tmp/$tmpfile
