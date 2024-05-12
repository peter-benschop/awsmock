//
// Created by vogje01 on 5/12/24.
//

#include <awsmock/service/s3/S3HashCreator.h>

namespace AwsMock::Service {

    void S3HashCreator::Run() {

        Core::Configuration &configuration = Core::Configuration::instance();
        std::string dataDir = configuration.getString("awsmock.data.dir", DEFAULT_DATA_DIR);

        std::string filename = dataDir + Poco::Path::separator() + _object.internalName;
        for (const auto &algorithm: _algorithms) {
            if (algorithm == "SHA1") {
                _object.sha1sum = Core::Crypto::GetSha1FromFile(filename);
            } else if (algorithm == "SHA256") {
                _object.sha256sum = Core::Crypto::GetSha256FromFile(filename);
            } else if (algorithm == "MD5") {
                _object.sha256sum = Core::Crypto::GetMd5FromFile(filename);
            }
            Database::S3Database::instance().UpdateObject(_object);
            log_debug << "Calculated hashes, key: " << _object.key << " hash: " << algorithm;
        }
    }

}// namespace AwsMock::Service
