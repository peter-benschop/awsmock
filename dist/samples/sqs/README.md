# SQS Examples

This directory contains examples for the use of the AwsMock AWS simulation package. Most of the features of AwsMock are covered in the different samples.

All example need a running awsmock manager listening on port 4566. If you prefer another port edit the sample bash script accordingly. To set a port of 9000 change the
line ```--endpoint http://localhost:4566``` to ```--endpoint http://localhost:9000```.

All examples are cleaning up after execution, so that the next example runs without errors.

This directory container the following SQS examples:

- ```create-queue.sh```: creates a new queue ```test-queue```
- ```delete-queue.sh```: deletes the queue ```test-queue```
