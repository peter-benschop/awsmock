# SSM Examples

This directory contains examples for the use of the AwsMock AWS simulation package. Most of the features of AwsMock are covered in the different samples.

All example need a running awsmock manager listening on port 4566. If you prefer another port edit the sample bash script accordingly. To set a port of 9000 change the
line ```--endpoint http://localhost:4566``` to ```--endpoint http://localhost:9000```.

All examples are cleaning up after execution, so that the next example runs without errors.

This directory container the following SSM examples:

- ```put-parameter.sh```: put a parameter with name ```test-name``` and value ```test-value``` into the SSM parameter store
- ```get-parameter.sh```: gets a parameter with name ```test-name``` and value ```test-value``` from the SSM parameter store
- ```describe-parameters.sh```: return s list of defined parameters from the SSM parameter store
- ```delete-parameter.sh```: deletes the parameter with name ```test-name``` from the SSM parameter store