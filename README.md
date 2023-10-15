# aws-mock

aws-mock is a high performance, persistent AWS simulation. Currently the following services are supported: 

- S3: Amazon Simple Storage Service
- SQS: Amazon Simple Queue Service
- SNS: Amazon Simple Notification Service
- Lambda: Amazon Lambda Service
- Transfer: Amazon transfer server, supporting an FTP server

aws-mock is written in C++ with a MongoDB persistence layer. All objects are stored in the database. The simulation 
reacts to all AWS commands send to the default port 4566. For a lists of supported command see below tables for the 
different AWS services.

## S3

Data is stored as objects within resources called “buckets”, and a single object can be up to 5 terabytes in size. 
Objects can be accessed through S3 Access Points or directly through the bucket hostname. With cost-effective storage 
classes and easy-to-use management features, you can optimize costs, organize data, and configure fine-tuned access 
controls to meet specific business, organizational, and compliance requirements.

AwsMock S3 mock simulates a real AWS S3 bucket and its object. They can be copied, added, moved, deleted any some more 
functions. S3 object are stored on disk and their metadata is part of AwsMock Mongo DB collection. Therefore the MongoDB 
has two collections: Buckets and Objects. Buckets contain the bucket metadata and teh object collection the object data.

See [AwsMock S3 supported commands](docs/S3/S3Functions.md) for a list of supported commands.

## SNS

Amazon Simple Notification Service (Amazon SNS) is a managed service that provides message delivery from publishers to 
subscribers (also known as producers and consumers). Publishers communicate asynchronously with subscribers by sending 
messages to a topic, which is a logical access point and communication channel. Clients can subscribe to the SNS topic 
and receive published messages using a supported endpoint type, such as Amazon Kinesis Data Firehose, Amazon SQS, 
AWS Lambda, HTTP, email, mobile push notifications, and mobile text messages (SMS).

Currently only SQS is supported as endpoint type.

See [AwsMock SNS supported commands](docs/SNS/SNSFunctions.md) for a list of supported commands.

## Getting started

### Building AwsMock

#### Minimum Requirements:
 
 - GNU Compiler Collection (GCC) 4.9 or later
 - OR Clang 3.3 or later
 - Aws SDK C++ installed (see [AWS SDK for C++](https://pocoproject.org/))
 - Poco installed (see [Simplify C++ development](https://pocoproject.org/))
 - MongoDB client C and CXX (see [MongoDB C++ driver](https://www.mongodb.com/docs/drivers/cxx/))
 - libcurl, libz, libssl, libcrypto, libarchive
 - 4GB of RAM.

#### Building from Source:
To create an out-of-source build:

 1. Install CMake and the relevant build tools for your platform. Ensure these are available in your executable path.
 2. Create your build directory. Replace <BUILD_DIR> with your build directory name:
 3. Build the project:
    ```
    cd <BUILD_DIR>
    cmake <path-to-root-of-this-source-code> -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=<path-to-install>
    cmake --build . --config=Debug
    cmake --install . --config=Debug
    ```
    
## SQS

Supported commands are:

| REST Api           | Description                   | Example                                                                                                              |
|--------------------|-------------------------------|----------------------------------------------------------------------------------------------------------------------|
| CreateQueue        | Create a new queue            | aws sqs create-queue --queue-name &lt;name&gt; --endpoint http://localhost:4566                                      |
| SendMessage        | Send a message to a queue     | aws sqs send-message --queue-url &lt;url&gt; --endpoint http://localhost:4566                                        |
| ReceiveMessage     | Receive messages from a queue | aws sqs receive-message --queue-url &lt;url&gt; --endpoint http://localhost:4566                                     |
| PurgeQueue         | Purge a queue                 | aws sqs purge-queue --queue-url &lt;url&gt; --endpoint http://localhost:4566                                         |
| GetQueueAttributes | Get queue attributes          | aws sqs get-queue-attributes --queue-url &lt;url&gt; --attribute-names All --endpoint http://localhost:4566          |
| SetQueueAttributes | Sets a queue attribute        | aws sqs set-queue-attributes --queue-url &lt;url&gt; --attributes &lt;value&gt; --endpoint http://localhost:4566     |
| DeleteMessage      | Deletes a message             | aws sqs delete-message --queue-url &lt;url&gt; --receipt-handle &lt;handle&gt; --endpoint http://localhost:4566      |
| DeleteQueue        | Deletes a queue               | aws sqs delete-queue --queue-url &lt;url&gt; --receipt-handle &lt;handle&gt; --endpoint http://localhost:4566 |

## SNS

Supported commands are:

| REST Api    | Description                       | Example                                                                                                     |
|-------------|-----------------------------------|-------------------------------------------------------------------------------------------------------------|
| CreateTopic | Creates a new SNS topic           | aws sns create-topic --name &lt;name&gt; --endpoint http://localhost:4566                                   |
| ListTopic   | Lists all topics                  | aws sns list-topic --endpoint http://localhost:4566                                                         | 
| Publish     | Publish a message to a topic      | aws sns publish --topic-arn&lt;arn&gt; --message &lt;message&gt; --endpoint http://localhost:4566           |
| Subscribe   | Subscribes an endpoint to a topic | aws sns subscribe --topic-arn&lt;arn&gt; --protocol &lt;protocol&gt; --endpoint http://localhost:4566       |
| Unsubscribe | Unsubscribe from a topic          | aws sns unsubscribe --subscription-arn&lt;arn&gt; --endpoint http://localhost:4566                          |
| Delete      | Deletes a topic                   | aws sns delete --topic-arn&lt;arn&gt; --endpoint http://localhost:4566 |
