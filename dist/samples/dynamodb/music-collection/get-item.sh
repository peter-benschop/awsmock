#!/bin/bash

aws dynamodb get-item \
--region eu-central-1 \
--table-name MusicCollection \
--key file://key.json \
--return-consumed-capacity TOTAL \
--endpoint http://localhost:4566 \
--profile awsmock
