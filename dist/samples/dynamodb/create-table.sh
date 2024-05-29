#!/bin/bash

aws dynamodb create-table \
--region eu-central-1 \
--table-name MusicCollection \
--attribute-definitions file://./resources/attributes.json \
--key-schema file://./resources/key-schema.json \
--provisioned-throughput file://./resources/capacity.json \
--tags file://./resources/tags.json \
--endpoint http://localhost:4566 \
--profile awsmock

