## Getting started

The lambda function need credentials (or they need to be setup not ot use credentials). Two files need to be included in
the ZIP file in order to set the authentication environment, ```config``` and ```credentials```. The access key ID and
the ```aws_secret_access_key``` can both be empty or ```none```, but they need to be defined.

### Build te zip file

In order to include the config and credential file, zip the lambda_function.py together with the config and credential
files:

```
zip python-events.zip config credentials lambda_function.py
```

Use the ```zip``` tool on Linux (gzip does not work, as it does not preserve the directory structure).

## Deploying your Python lambda function

Use the ```deploy.sh``` bash script to deploy your Python lambda function to AwsMock. It used the environment in
the ```resources``` directory. After deployment, you need to wait a moment, as AwsMock is creating the docker images and
the deployment of the image to docker as an asynchronous task.

You see when the lambda is deployed, when the ```docker ps``` shows the lambda:

```
$> docker ps
CONTAINER ID   IMAGE                                COMMAND                  CREATED          STATUS          PORTS                                         NAMES
7d711ded509e   python-events:latest                 "/lambda-entrypoint.…"   19 seconds ago      Up 18 seconds      0.0.0.0:49543->8080/tcp, :::49543->8080/tcp   python-events
```

## Invoking your lambda function

Use the ```invoke.sh``` bash script to invoke the Python lambda function. AwsMock will send the invocation request to
the docker container, which is listening for invocation request on a random port. The random port is mapped to the
lambda runtime standard port 8080 inside the docker container. The random port will be between 32768 and 65535.

## See the lambda function logs

In order to see the lambda logs use:

```
$> docker ps
CONTAINER ID   IMAGE                                COMMAND                  CREATED             STATUS             PORTS                                         NAMES
7d711ded509e   python-events:latest                 "/lambda-entrypoint.…"   19 seconds ago      Up 18 seconds      0.0.0.0:49543->8080/tcp, :::49543->8080/tcp   python-events
docker logs -f 7d711ded509e
```

This will send the logs to stdout using tail mode. As the lambda function runs as docker container, you can see the logs
also when the lambda invocation has already finished.

## Internals

AwsMock always requires ZIP files to be used be the create-lambda function (S3 deployments are not supported at the
moment). AwsMock takes the ZIP file and creates an image for you. The Python runtime takes internally the following
Dockerfile:

```
FROM public.ecr.aws/lambda/python:3.x
ENV environment values
...
COPY requirements.txt ${LAMBDA_TASK_ROOT}
RUN mkdir -p /root/.aws
COPY config /root/.aws
COPY credentials /root/.aws
RUN pip install -r requirements.txt
COPY lambda_function.py ${LAMBDA_TASK_ROOT}
CMD [handler]
```
