# aws-mock

aws-mock is a high performance, persistent AWS simulation. Currently the following services are supported: 

- S3: Amazon Simple Storage Service
- SQS: Amazon Simple Queue Service
- SNS: Amazon Simple Notification Service
- Lambda: Amazon Lambda Service

aws-mock is written in C++ with a MongoDB persistence layer. All objects are stored in the database. The simulation 
reacts to all AWS commands send to the default port 4567. For a lists of supported command see below tables for the 
different AWS services.

## S3

Data is stored as objects within resources called “buckets”, and a single object can be up to 5 terabytes in size. Objects can be accessed through S3 Access Points or directly through 
the bucket hostname. With cost-effective storage classes and easy-to-use management features, you can optimize costs, organize data, and configure fine-tuned access controls to meet 
specific business, organizational, and compliance requirements.

AwsMock S3 mock simulates a real AWS S3 bucket and its object. They can be copied, added, moved, deleted any some more functions. S3 object are stored on disk and their metadata is part of
AwsMock Mongo DB collection. Therefore the MongoDB has two collections: Buckets and Objects. Buckets contain the bucket metadata and teh object collection the object data.

See [AwsMock S3 supported commands](docs/S3/S3Functions) for a list of supported commands.

## SQS

Supported commands are:

| REST Api           | Description                   | Example                                                                                                              |
|--------------------|-------------------------------|----------------------------------------------------------------------------------------------------------------------|
| CreateQueue        | Create a new queue            | aws sqs create-queue --queue-name &lt;name&gt; --endpoint http://localhost:4567                                      |
| SendMessage        | Send a message to a queue     | aws sqs send-message --queue-url &lt;url&gt; --endpoint http://localhost:4567                                        |
| ReceiveMessage     | Receive messages from a queue | aws sqs receive-message --queue-url &lt;url&gt; --endpoint http://localhost:4567                                     |
| PurgeQueue         | Purge a queue                 | aws sqs purge-queue --queue-url &lt;url&gt; --endpoint http://localhost:4567                                         |
| GetQueueAttributes | Get queue attributes          | aws sqs get-queue-attributes --queue-url &lt;url&gt; --attribute-names All --endpoint http://localhost:4567          |
| SetQueueAttributes | Sets a queue attribute        | aws sqs set-queue-attributes --queue-url &lt;url&gt; --attributes &lt;value&gt; --endpoint http://localhost:4567     |
| DeleteMessage      | Deletes a message             | aws sqs delete-message --queue-url &lt;url&gt; --receipt-handle &lt;handle&gt; --endpoint http://localhost:4567      |
| DeleteQueue        | Deletes a queue               | aws sqs delete-queue --queue-url &lt;url&gt; --receipt-handle &lt;handle&gt; --endpoint http://localhost:4567 |

## SNS

Supported commands are:

| REST Api    | Description                       | Example                                                                                                     |
|-------------|-----------------------------------|-------------------------------------------------------------------------------------------------------------|
| CreateTopic | Creates a new SNS topic           | aws sns create-topic --name &lt;name&gt; --endpoint http://localhost:4567                                   |
| ListTopic   | Lists all topics                  | aws sns list-topic --endpoint http://localhost:4567                                                         | 
| Publish     | Publish a message to a topic      | aws sns publish --topic-arn&lt;arn&gt; --message &lt;message&gt; --endpoint http://localhost:4567           |
| Subscribe   | Subscribes an endpoint to a topic | aws sns subscribe --topic-arn&lt;arn&gt; --protocol &lt;protocol&gt; --endpoint http://localhost:4567       |
| Unsubscribe | Unsubscribe from a topic          | aws sns unsubscribe --subscription-arn&lt;arn&gt; --endpoint http://localhost:4567                          |
| Delete      | Deletes a topic                   | aws sns delete --topic-arn&lt;arn&gt; --endpoint http://localhost:4567 |
