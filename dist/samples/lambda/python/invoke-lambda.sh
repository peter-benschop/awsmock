#!/bin/bash

# Invoke function
aws lambda invoke \
  --function-name python-events \
  --payload fileb://./resources/event.json \
  --log-type Tail \
  --region eu-central-1 \
  --endpoint http://localhost:4566 \
  --profile awsmock \
  out.json
