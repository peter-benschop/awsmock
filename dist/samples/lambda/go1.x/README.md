# AwsMock Lambda Go 1.x samples

## Getting started

The lambda function need credentials (or they need to be setup not ot use credentials). Two files need to be included in
the ZIP file in order to set the authentication environment, ```config``` and ```credentials```. The access key ID and
the ```aws_secret_access_key``` can both be empty or ```none```, but they need to be defined.

### Compiling you Go lambda function

In order to compile your Go lambda function, make sure that the output executable is called ```bootstrap```. This is due
to the fact that the Go Lambda runtime does not exist anymore, and is replaces by the normal Amazon Linux 2023 provided
runtime (```provided.al2023```) and this does not have a handler anymore, but executes the lambda function as is.
Therefore, the compilation should be as:

```
go build -o bootstrap main.go
```

After you have compiled your Go lambda function, zip them together with the config and credential files:

```
zip blank-go.zip config credentials bootstrap
```

Use the ```zip``` tool on Linux (gzip does not work, as it does not preserve the directory structure).

If you are running the AwsMock manager on the docker host machine you need to change the endpoint the lambda is invoking
for AWS connections.

```
var client = lambda.New(session.New())

func handleRequest(ctx context.Context, event events.SQSEvent) (string, error) {
    client.Endpoint = *aws.String(os.Getenv("AWS_ENDPOINT"))
    ....
}
```

The endpoint is defined as environment variable during creation of the lambda docker image. See the example environment
file at ```dist/samples/lambda/resources/go-lambda-env.json```:

```
{
  "Variables": {
    "AWS_REGION": "eu-central-1",
    "AWS_ACCOUNT_ID": "000000000000",
    "AWS_ACCESS_KEY_ID": "none",
    "AWS_SECRET_ACCESS_KEY": "none",
    "AWS_SESSION_TOKEN": "none",
    "AWS_PROFILE": "awsmock",
    "AWS_ENDPOINT": "http://host.docker.internal:4566"
  }
}
```

The environment gets loaded during lambda function creation:

```
aws lambda create-function \
  ...
  --environment file://./resources/go-lambda-env.json \
  ...
```

In case the AwsMock simulation itself runs as a docker image you can use localhost instead:

```
{
  "Variables": {
    "AWS_REGION": "eu-central-1",
    "AWS_ACCOUNT_ID": "000000000000",
    "AWS_ACCESS_KEY_ID": "none",
    "AWS_SECRET_ACCESS_KEY": "none",
    "AWS_SESSION_TOKEN": "none",
    "AWS_PROFILE": "awsmock",
    "AWS_ENDPOINT": "http://localhost:4566"
  }
}
```

If you don't set the endpoint environment variable the lambda function will try to connect to the real AWS cloud of the
region you supplied.

## Deploying your Go lambda function

Use the ```deploy.sh``` bash script to deploy your Go lambda function to AwsMock. It used the environment in
the ```resources``` directory. After deployment, you need to wait a moment, as AwsMock is creating the docker images and
the deployment of the image to docker as an asynchronous task.

You see when the lambda is deployed, when the ```docker ps``` shows the lambda:

```
$> docker ps
CONTAINER ID   IMAGE                                COMMAND                  CREATED          STATUS          PORTS                                         NAMES
da9aa3306be5   blank-go:latest                      "/lambda-entrypoint.…"   4 seconds ago    Up 4 seconds    0.0.0.0:34939->8080/tcp, :::34939->8080/tcp   blank-go
```

## Invoking your lambda function

Use the ```invoke.sh``` bash script to invoke the Go lambda function. AwsMock will send the invocation request to the
docker container, which is listening for invocation request on a random port. The random port is mapped to the lambda
runtime standard port 8080 inside the docker container. The random port will be between 32768 and 65535.

## See the lambda function logs

In order to see the lambda logs use:

```
$> docker ps
CONTAINER ID   IMAGE                                COMMAND                  CREATED          STATUS          PORTS                                         NAMES
da9aa3306be5   blank-go:latest                      "/lambda-entrypoint.…"   4 seconds ago    Up 4 seconds    0.0.0.0:34939->8080/tcp, :::34939->8080/tcp   blank-go
docker logs -f da9aa3306be5
```

This will send the logs to stdout using tail mode. As the lambda function runs as docker container, you can see the logs
also when the lambda invocation has already finished.

## Internals

AwsMock always requires ZIP files to be used be the create-lambda function (S3 deployments are not supported at the
moment). AwsMock takes the ZIP file and creates an image for you. The Go runtime takes internally the following
Dockerfile:

```
FROM public.ecr.aws/lambda/provided:al2023;
ENV AWS_ENDPOINT http://host.internal.docker:4566
....
COPY bootstrap ${LAMBDA_RUNTIME_DIR}
RUN chmod 755 ${LAMBDA_RUNTIME_DIR}/bootstrap
RUN mkdir -p /root/.aws
COPY config /root/.aws
COPY credentials /root/.aws
CMD [handler]
```

As already mentioned above the handler is irrelevant, as the Amazon Linux 2023 runtime takes the bootstrap file in the
```/var/runtime``` directory.