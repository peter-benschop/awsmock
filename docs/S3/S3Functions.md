
# Supported S3 commands 

For compatibility reasons the JSON attributes are always stored in files and the ```file://<filename>``` is used to add the attribute value to the command, for instance
```
aws put-bucket-notification-configuration --bucket &lt;bucket&gt; --notification-configuration file://<hook-file> --endpoint http://localhost:4566|
```
The actual bucket notification configuration is stored in the ```<hook-file>```:
```
{
  "LambdaFunctionConfigurations": [
    {
      "Id": "1234566890123",
      "LambdaFunctionArn": "arn:aws:lambda:eu-central-1:000000000000:function:ftp-file-copy",
      "Events": [
        "s3:ObjectCreated:*"
      ]
    }
  ]
}
```
This makes it simpler to use the same command on Windows and Linux system, as Windows has another escape syntax as a normal Linux system. 

Supported commands are:

| REST Api              | Description                                   | Example                                                                                                                 |
|-----------------------|-----------------------------------------------|-------------------------------------------------------------------------------------------------------------------------|
| CreateBucket          | Create a new bucket                           | aws s3 create-bucket &lt;bucket&gt; --endpoint http://localhost:4566                                                    |
| PutObject             | Upload an object to an S3 bucket              | aws s3 cp &lt;file&gt; s3://&lt;bucket&gt; --endpoint http://localhost:4566                                             |
| GetObject             | Download a object from a S3 bucket            | aws s3 cp s3://bucket &lt;file&gt; --endpoint http://localhost:4566                                                     |
| ListAllBucket         | List all buckets                              | aws s3 ls --endpoint http://localhost:4566                                                                              |
| ListBucket            | List the content of a bucket                  | aws s3 ls s3://&lt;bucket&gt; --recursive --endpoint http://localhost:4566                                              |
| PutBucketNotification | Adds a notification configuration to a bucket | aws put-bucket-notification-configuration --bucket &lt;bucket&gt; --notification-configuration file://&lt;hook-file&gt; --endpoint http://localhost:4566|
| DeleteObject          | Deletes an object from a bucket               | aws rm &lt;s3Uri&gt; --endpoint http://localhost:4566                                                                                                   |
| DeleteBucket          | Deletes a bucket and all of its content       | aws rb &lt;s3Uri&gt; --endpoint http://localhost:4566                                                                                                    |
