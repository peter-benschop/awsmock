# aws-mock

aws-mock is a high performance, persistent AWS simulation. Currently, the following services are supported: 

- [S3](docs/man/awsmocks3.1.md): Amazon Simple Storage Service
- [SQS](docs/man/awsmocksqs.1.md): Amazon Simple Queue Service
- [SNS](docs/man/awsmocksns.1.md): Amazon Simple Notification Service
- [Lambda](docs/man/awsmocklambda.1.md): Amazon Lambda service
- [Cognito](docs/man/awsmockcognito.1.md): Amazon Cognito identity service
- [DynamoDB](docs/man/awsmockdynamodb.1.md): Amazon Dynamo database service
- [Transfer](docs/man/awsmocktransfer.1.md): Amazon transfer server, supporting FTP or SFTP servers

aws-mock is written in C++ with a MongoDB persistence layer. All objects are stored in the database. The simulation 
reacts to all AWS commands send to the default port 4566. For a lists of supported command see below tables for the 
different AWS services.

AwsMock can also be used without persistence layer (for instances used as a test-container). In this cas the 
configuration and all objects are stored in a in-memory database. As soon as the awsmock manager gos own all 
infrastructure and runtime objects are lost.

## S3 module

Data is stored as objects within resources called “buckets”, and a single object can be up to 5 terabytes in size. 
Objects can be accessed through S3 Access Points or directly through the bucket hostname. With cost-effective storage 
classes and easy-to-use management features, you can optimize costs, organize data, and configure fine-tuned access 
controls to meet specific business, organizational, and compliance requirements.

AwsMock S3 mock simulates a real AWS S3 bucket and its object. They can be copied, added, moved, deleted any some more 
functions. S3 object are stored on disk and their metadata is part of AwsMock Mongo DB collection. Therefore the MongoDB 
has two collections: Buckets and Objects. Buckets contain the bucket metadata and teh object collection the object data.

See [AwsMock S3 supported commands](docs/man/awsmocks3.1.md) in the supplied man page.

## SQS module

Simple Queue Service (SQS) is a managed messaging service offered by AWS. It allows you to decouple different components
of your applications by enabling asynchronous communication through message queues. SQS allows you to reliably send, store,
and receive messages with support for standard and FIFO queues.

AwsMock allows you to use the SQS APIs in your local environment to integrate and decouple distributed systems via
hosted queues. The supported APIs are available on our API coverage page, which provides information on the extent of
SQS’s integration with AwsMock.

See [AwsMock SQS supported commands](docs/man/awsmocksqs.1.md) for a list of supported commands.

## SNS module 

Amazon Simple Notification Service (Amazon SNS) is a managed service that provides message delivery from publishers to
subscribers (also known as producers and consumers). Publishers communicate asynchronously with subscribers by sending
messages to a topic, which is a logical access point and communication channel. Clients can subscribe to the SNS topic
and receive published messages using a supported endpoint type, such as Amazon Kinesis Data Firehose, Amazon SQS,
AWS Lambda, HTTP, email, mobile push notifications, and mobile text messages (SMS).

Currently only SQS is supported as endpoint type.

See [AwsMock SNS supported commands](docs/man/awsmocksns.1.md) for a list of supported commands.

## Lambdas module

AWS Lambda is a Serverless Function as a Service (FaaS) platform that lets you run code in your preferred programming 
language on the AWS ecosystem. AWS Lambda automatically scales your code to meet demand and handles server provisioning, 
management, and maintenance. AWS Lambda allows you to break down your application into smaller, independent functions 
that integrate seamlessly with AWS services.

AwsMock supports Lambdas, allowing you to use the Lambda API to create, deploy, and test your Lambda functions. The 
supported APIs are available on our Lambda coverage page, which provides information on the extent of Lambda’s 
integration with AwsMock.

See [AwsMock Lambda supported commands](docs/man/awsmocklambda.1.md) for a list of supported commands.

## Getting started

### Building AwsMock

#### Minimum Requirements:
 
 - GNU Compiler Collection (GCC) 4.9 or later
 - OR Clang 3.3 or later
 - Aws SDK C++ installed (see [AWS SDK for C++](https://pocoproject.org/))
 - Poco installed (see [Simplify C++ development](https://pocoproject.org/))
 - MongoDB C and CXX clients (see [MongoDB C++ driver](https://www.mongodb.com/docs/drivers/cxx/))
 - libcurl, libz, libssl, libcrypto, libarchive, libtbb
 - 4GB of RAM.

#### Building from Source:

Building AwsMock from scratch is a rather time-consuming procedure. For a first glance at AwsMock, better use the provided
docker image. Nevertheless, if you need to compile it by your own, here are the instructions.

To create an out-of-source build:

 1. Install CMake and the relevant build tools for your platform. Ensure these are available in your executable path.
 2. Download the source tree
    ```
    git clone https://github.com/jensvogt/aws-mock.git
    cd aws-mock
    ```
 3. Build the project:
    ```
    cmake . -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=<path-to-install>
    cmake --build . --config=Debug
    ```
 4. Install the executables, libraries and man pages:
    ```
    cmake --install . --config=Debug
    ```
 5. Start the manager:
    ```
    awsmockmgr --deamon --loglevel debug
    ```
    
As already said, this can be a time-consuming procedure, depending on your machine and the environment.

### Using the docker image

Using the provided docker image is much simpler (assuming Docker is already installed).

To start the docker image:
  1. Pull the docker image:
  ```
  docker pull jensvogt/aws-mock:latest
  ```
  2. Start the container
  ```
  docker run -p 4566:4566 -p 4567:4567 jensvogt/aws-mock:latest
  ```
This invocation will run with the in-memory database, as the alpine image does not have a own MongoDb instance. 

To connect a MongoDB instance use the provided docker-compose file:
  ```
  cd docker
  docker-compose up
  ```
