## Introduction

This directory contains the AwsMock Lambda examples. Lambda functions in general (either in Java, Python, Go or Rust)
are running as docker container. Therefore, you need have docker installed on your system using the AWS RIE environment
runtime. RIE does not allow concurrent execution of lambda functions as Docker images. Therefore, AwsMock (as any
other AWS simulation, like Localstack) is running the Lambda function sequentially.

The examples are using Go 1.19.8 on Amazon Linux 2023. If you want to run your own Go Lambda function you need to
compile the Go source on a Amazon Linux 2023 machine (either as docker image or Windows WSL2) machine. Otherwise, you
will get problem with non-matching GLIBC versions. The Go executables are compile using Go 1.19.8 on Amazon Linux 2023.

## Getting started

The lambda function need credentials (or they need to be setup not ot use credentials). Two files need to be included in
the ZIP file in order to set the authentication environment, ```config``` and ```credentials```. The access key ID and
the ```aws_secret_access_key``` can both be empty or ```none```, but they need to be defined.

## Supported Runtimes

The following lambda runtimes are supported:

- java8: AWS Java 8 runtime
- java11: AWS Java 11 runtime
- java17: AWS Java 17 runtime
- java21: AWS Java 21 runtime
- python 3.8: AWS Python 3.8 runtime (if possible don't use, it will be deprecated soon)
- python 3.9: AWS Python 3.9 runtime
- python 3.10: AWS Python 3.10 runtime
- python 3.11: AWS Python 3.11 runtime
- python 3.12: AWS Python 3.12 runtime
- provided: Amazon Linux (for C++ lambdas)
- provided.al2023: Amazon Linux 2023 (for C++ lambdas)
- go1.x: AWS Amazon Linux 2023 (see [go1.x runtime](./go1.x/README:md) for details)
- nodejs.16: AWS Node.js 16 runtime (if possible don't use, it will be deprecated soon)
- nodejs.18: AWS Node.js 18 runtime
- nodejs.20: AWS Node.js 20 runtime

For a list of supported runtimes
see [Lambda runtimes](https://docs.aws.amazon.com/lambda/latest/dg/lambda-runtimes.html).
Windows runtimes (.Net6, .Net8, .Net 8) are not supported yet.