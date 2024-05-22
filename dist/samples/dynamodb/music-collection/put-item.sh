#!/bin/bash

aws dynamodb put-item \
--region eu-central-1 \
--table-name MusicCollection \
--item file://put-item.json \
--return-consumed-capacity TOTAL \
--return-item-collection-metrics SIZE \
--endpoint http://localhost:4566 \
--profile awsmock
