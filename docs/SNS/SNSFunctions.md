
# Supported SNS commands 

Supported commands are:

| REST Api    | Description                       | Example                                                                                                     |
|-------------|-----------------------------------|-------------------------------------------------------------------------------------------------------------|
| CreateTopic | Creates a new SNS topic           | aws sns create-topic --name &lt;name&gt; --endpoint http://localhost:4566                                   |
| ListTopic   | Lists all topics                  | aws sns list-topic --endpoint http://localhost:4566                                                         | 
| Publish     | Publish a message to a topic      | aws sns publish --topic-arn&lt;arn&gt; --message &lt;message&gt; --endpoint http://localhost:4566           |
| Subscribe   | Subscribes an endpoint to a topic | aws sns subscribe --topic-arn&lt;arn&gt; --protocol &lt;protocol&gt; --endpoint http://localhost:4566       |
| Unsubscribe | Unsubscribe from a topic          | aws sns unsubscribe --subscription-arn&lt;arn&gt; --endpoint http://localhost:4566                          |
| Delete      | Deletes a topic                   | aws sns delete --topic-arn&lt;arn&gt; --endpoint http://localhost:4566 |