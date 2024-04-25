//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_KMS_MASTER_KEY_SPEC_H
#define AWSMOCK_DTO_KMS_MASTER_KEY_SPEC_H

// C++ includes
#include <map>
#include <string>

namespace AwsMock::Dto::Kms {

    /**
     * KMS master key specification
     *
     * @author jens.vogt@opitz-consulting.com
     */
    enum class CustomerMasterKeySpec {
        RSA_2048,
        RSA_3072,
        RSA_4096,
        ECC_NIST_P256,
        ECC_NIST_P384,
        ECC_NIST_P521,
        ECC_SECG_P256K1,
        SYMMETRIC_DEFAULT,
        HMAC_224,
        HMAC_256,
        HMAC_384,
        HMAC_512,
        SM2
    };

    static std::map<CustomerMasterKeySpec, std::string> CustomerMasterKeySpecNames{
            {CustomerMasterKeySpec::RSA_2048, "RSA_2048"},
            {CustomerMasterKeySpec::RSA_3072, "RSA_3072"},
            {CustomerMasterKeySpec::RSA_4096, "RSA_4096"},
            {CustomerMasterKeySpec::ECC_NIST_P256, "ECC_NIST_P256"},
            {CustomerMasterKeySpec::ECC_NIST_P384, "ECC_NIST_P384"},
            {CustomerMasterKeySpec::ECC_NIST_P521, "ECC_NIST_P521"},
            {CustomerMasterKeySpec::ECC_SECG_P256K1, "ECC_SECG_P256K1"},
            {CustomerMasterKeySpec::SYMMETRIC_DEFAULT, "SYMMETRIC_DEFAULT"},
            {CustomerMasterKeySpec::HMAC_224, "HMAC_224"},
            {CustomerMasterKeySpec::HMAC_256, "HMAC_256"},
            {CustomerMasterKeySpec::HMAC_384, "HMAC_384"},
            {CustomerMasterKeySpec::HMAC_512, "HMAC_512"},
            {CustomerMasterKeySpec::SM2, "SM2"},
    };

    [[maybe_unused]] static std::string CustomerMasterKeySpecToString(CustomerMasterKeySpec customerMasterKeySpec) {
        return CustomerMasterKeySpecNames[customerMasterKeySpec];
    }

    [[maybe_unused]] static CustomerMasterKeySpec CustomerMasterKeySpecFromString(const std::string &customerMasterKeySpec) {
        for (auto &it: CustomerMasterKeySpecNames) {
            if (it.second == customerMasterKeySpec) {
                return it.first;
            }
        }
        return CustomerMasterKeySpec::SYMMETRIC_DEFAULT;
    }

}// namespace AwsMock::Dto::Kms

#endif// AWSMOCK_DTO_KMS_MASTER_KEY_SPEC_H
