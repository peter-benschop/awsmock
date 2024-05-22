#!/bin/bash

aws s3 mb s3://test-bucket \
--region eu-central-1 \
--endpoint http://localhost:4566 \
--profile awsmock

