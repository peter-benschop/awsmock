#!/bin/bash

aws dynamodb create-table \
--region eu-central-1 \
--table-name MusicCollection \
--attribute-definitions file://./attributes.json \
--key-schema file://./key-schema.json \
--provisioned-throughput file://./capacity.json \
--tags file://./tags.json \
--endpoint http://localhost:4566 \
--profile awsmock

