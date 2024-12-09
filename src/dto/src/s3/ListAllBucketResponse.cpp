//
// Created by vogje01 on 30/05/2023.
//

// AwsMock includes
#include <awsmock/dto/s3/ListAllBucketResponse.h>

namespace AwsMock::Dto::S3 {

    std::string ListAllBucketResponse::ToXml() const {

        boost::property_tree::ptree root;
        root.add("ListAllMyBucketsResult.Total", total);

        boost::property_tree::ptree bucketsTree;
        for (auto &it: bucketList) {
            boost::property_tree::ptree bucketTree;
            bucketTree.add("BucketRegion", it.region);
            bucketTree.add("Name", it.name);
            bucketTree.add("CreationDate", Core::DateTimeUtils::ToISO8601(it.created));
            bucketsTree.push_back(std::make_pair("Bucket", bucketTree));
        }
        root.add_child("ListAllMyBucketsResult.Buckets", bucketsTree);
        return Core::XmlUtils::ToXmlString(root);
    }

    std::string ListAllBucketResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListAllBucketResponse &r) {
        os << "ListAllBucketResponse={bucketList='";
        for (const auto &it: r.bucketList) {
            os << it.ToString() + ", ";
        }
        os << "'}";
        return os;
    }

}// namespace AwsMock::Dto::S3
