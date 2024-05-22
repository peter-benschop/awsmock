#!/bin/bash

aws dynamodb delete-item \
--region eu-central-1 \
--table-name MusicCollection \
--key file://key.json \
--return-values ALL_OLD \
--return-consumed-capacity TOTAL \
--return-item-collection-metrics SIZE \
--endpoint http://localhost:8000 \
--profile awsmock
