#!/bin/bash

# Create temp files
tmpfile=$(mktemp -p /tmp).txt
fallocate -l 10G $tmpfile
tmpfile=$(basename $tmpfile)

# Copy to S3 bucket
aws s3 cp /tmp/$tmpfile s3://test-bucket/$tmpfile \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

# List bucket content
aws s3 ls s3://test-bucket \
--recursive \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

# Cleanup
rm -f /tmp/$tmpfile
