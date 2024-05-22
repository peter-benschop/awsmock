#!/bin/bash

# Create some files
for i in {1..5}
do
  tmpfile=$(mktemp -p /tmp).txt
  base64 /dev/urandom | head -c 1k > $tmpfile
  filearray[$i]=$(basename $tmpfile)
done

# Copy to S3 bucket
i=0
for file in "${filearray[@]}"
do
  key=dir$i
  aws s3 cp /tmp/$file s3://test-bucket/$key/$file --region eu-central-1 --endpoint http://localhost:4566 --profile awsmock
  i=$(($i+1))
done

# List bucket content
aws s3 ls s3://test-bucket \
--recursive \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

# Cleanup
for file in "${filearray[@]}"
do
  rm -f /tmp/$file
done


