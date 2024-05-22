#!/bin/bash

aws dynamodb delete-table \
--region eu-central-1 \
--table-name MusicCollection \
--profile awsmock

