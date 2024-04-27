//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/core/CryptoUtils.h>

namespace AwsMock::Core {

    unsigned int Crypto::_salt[] = {1214370622, 264849915};

    std::string Crypto::GetMd5FromString(const std::string &content) {

        EVP_MD_CTX *context = EVP_MD_CTX_new();
        const EVP_MD *md = EVP_md5();
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;
        std::string output;

        EVP_DigestInit(context, md);
        EVP_DigestUpdate(context, reinterpret_cast<const unsigned char *>(content.c_str()), content.length());
        EVP_DigestFinal(context, md_value, &md_len);
        EVP_MD_CTX_free(context);

        output.resize(md_len * 2);
        for (unsigned int i = 0; i < md_len; ++i)
            std::sprintf(&output[i * 2], "%02x", md_value[i]);
        return output;
    }

    std::string Crypto::GetMd5FromFile(const std::string &fileName) {

        char *buffer = new char[AWSMOCK_BUFFER_SIZE];

        EVP_MD_CTX *context = EVP_MD_CTX_new();
        const EVP_MD *md = EVP_md5();
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;
        std::string output;

        EVP_DigestInit(context, md);

        std::ifstream ifs(fileName, std::ios::binary);
        while (ifs.good()) {
            ifs.read(buffer, AWSMOCK_BUFFER_SIZE);
            EVP_DigestUpdate(context, buffer, ifs.gcount());
        }
        ifs.close();

        EVP_DigestFinal(context, md_value, &md_len);
        EVP_MD_CTX_free(context);

        output.resize(md_len * 2);
        for (unsigned int i = 0; i < md_len; ++i)
            std::sprintf(&output[i * 2], "%02x", md_value[i]);
        delete[] buffer;
        return output;
    }

    std::string Crypto::GetSha1FromString(const std::string &content) {

        EVP_MD_CTX *context = EVP_MD_CTX_new();
        const EVP_MD *md = EVP_sha1();
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;
        std::string output;

        EVP_DigestInit_ex(context, md, nullptr);
        EVP_DigestUpdate(context, content.c_str(), content.length());
        EVP_DigestFinal_ex(context, md_value, &md_len);
        EVP_MD_CTX_free(context);

        output.resize(md_len * 2);
        for (unsigned int i = 0; i < md_len; ++i)
            std::sprintf(&output[i * 2], "%02x", md_value[i]);
        return output;
    }

    std::string Crypto::GetSha1FromFile(const std::string &fileName) {

        char *buffer = new char[AWSMOCK_BUFFER_SIZE];

        EVP_MD_CTX *context = EVP_MD_CTX_new();
        const EVP_MD *md = EVP_sha1();
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;
        std::string output;

        EVP_DigestInit_ex(context, md, nullptr);

        std::ifstream is;
        is.open(fileName.c_str(), std::ios::binary);
        while (is.good()) {
            is.read(buffer, AWSMOCK_BUFFER_SIZE);
            EVP_DigestUpdate(context, buffer, is.gcount());
        }
        is.close();

        EVP_DigestFinal_ex(context, md_value, &md_len);
        EVP_MD_CTX_free(context);

        output.resize(md_len * 2);
        for (unsigned int i = 0; i < md_len; ++i)
            std::sprintf(&output[i * 2], "%02x", md_value[i]);
        delete[] buffer;
        return output;
    }

    std::string Crypto::GetSha256FromString(const std::string &content) {

        EVP_MD_CTX *context = EVP_MD_CTX_create();
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;
        std::string output;

        EVP_DigestInit_ex(context, EVP_sha256(), nullptr);
        EVP_DigestUpdate(context, content.c_str(), content.size());
        EVP_DigestFinal(context, md_value, &md_len);
        EVP_MD_CTX_free(context);

        output.resize(md_len * 2);
        for (unsigned int i = 0; i < md_len; ++i)
            std::sprintf(&output[i * 2], "%02x", md_value[i]);
        return output;
    }

    std::string Crypto::GetHmacSha256FromString(const std::string &key, const std::string &msg) {

        std::array<unsigned char, EVP_MAX_MD_SIZE> hash{};
        unsigned int hashLen;

        HMAC(EVP_sha256(),
             msg.data(),
             static_cast<int>(msg.size()),
             reinterpret_cast<unsigned char const *>(key.data()),
             static_cast<int>(key.size()),
             hash.data(),
             &hashLen);

        std::string output;
        output.resize(hashLen * 2);
        for (unsigned int i = 0; i < hashLen; ++i)
            std::sprintf(&output[i * 2], "%02x", hash[i]);
        return output;
    }

    std::string Crypto::GetSha256FromFile(const std::string &fileName) {

        char *buffer = new char[AWSMOCK_BUFFER_SIZE];

        EVP_MD_CTX *context = EVP_MD_CTX_new();
        const EVP_MD *md = EVP_sha256();
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;
        std::string output;

        EVP_DigestInit_ex(context, md, nullptr);

        std::ifstream is;
        is.open(fileName.c_str(), std::ios::binary);
        while (is.good()) {
            is.read(buffer, AWSMOCK_BUFFER_SIZE);
            EVP_DigestUpdate(context, buffer, is.gcount());
        }
        is.close();

        EVP_DigestFinal_ex(context, md_value, &md_len);
        EVP_MD_CTX_free(context);

        output.resize(md_len * 2);
        for (unsigned int i = 0; i < md_len; ++i)
            std::sprintf(&output[i * 2], "%02x", md_value[i]);

        delete[] buffer;

        return output;
    }

    std::string Crypto::GetHmacSha256FromString(const std::array<unsigned char, EVP_MAX_MD_SIZE> &key, const std::string &msg) {

        std::array<unsigned char, EVP_MAX_MD_SIZE> hash{};
        unsigned int hashLen;

        HMAC(EVP_sha256(),
             msg.data(),
             static_cast<int>(msg.size()),
             reinterpret_cast<unsigned char const *>(key.data()),
             static_cast<int>(key.size()),
             hash.data(),
             &hashLen);
        return HexEncode(hash.data(), hash.size());
    }

    std::array<unsigned char, EVP_MAX_MD_SIZE> Crypto::GetHmacSha256FromStringRaw(const std::string &key, const std::string &msg) {

        std::array<unsigned char, EVP_MAX_MD_SIZE> hash{};
        unsigned int hashLen;

        HMAC(EVP_sha256(),
             msg.data(),
             static_cast<int>(msg.size()),
             reinterpret_cast<unsigned char const *>(key.data()),
             static_cast<int>(key.size()),
             hash.data(),
             &hashLen);
        return hash;
    }

    std::array<unsigned char, EVP_MAX_MD_SIZE> Crypto::GetHmacSha256FromStringRaw(const std::array<unsigned char, EVP_MAX_MD_SIZE> &key, const std::string &msg) {

        std::array<unsigned char, EVP_MAX_MD_SIZE> hash{};
        unsigned int hashLen;

        HMAC(EVP_sha256(),
             msg.data(),
             static_cast<int>(msg.size()),
             reinterpret_cast<unsigned char const *>(key.data()),
             static_cast<int>(key.size()),
             hash.data(),
             &hashLen);
        return hash;
    }

    void Crypto::CreateAes256Key(unsigned char *key, unsigned char *iv) {

        if (RAND_bytes(key, CRYPTO_AES256_KEY_SIZE) < 0) {
            log_error << "Failed to generate 256bit random key";
        }
        if (RAND_bytes(iv, CRYPTO_AES256_BLOCK_SIZE) < 0) {
            log_error << "Failed to generate 128bit random iv";
        }
    }

    unsigned char *Crypto::Aes256EncryptString(unsigned char *plaintext, int *len, unsigned char *key) {

        // "opaque" encryption, decryption ctx structures that libcrypto uses to record status of enc/dec operations
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

        auto *key_data = key;
        int key_data_len = (int) strlen(reinterpret_cast<const char *>(key_data));

        if (Aes256EncryptionInit(key_data, key_data_len, (unsigned char *) &_salt, ctx)) {
            log_error << "Couldn't initialize AES256 cipher";
            return {};
        }

        /* max ciphertext len for a n bytes of plaintext is n + AES_BLOCK_SIZE -1 bytes */
        int c_len = *len + CRYPTO_AES256_BLOCK_SIZE, f_len = 0;
        auto *ciphertext = static_cast<unsigned char *>(malloc(c_len));

        // Allows reusing of 'ctx' for multiple encryption cycles
        EVP_EncryptInit_ex(ctx, nullptr, nullptr, nullptr, nullptr);
        EVP_EncryptUpdate(ctx, ciphertext, &c_len, plaintext, *len);
        EVP_EncryptFinal_ex(ctx, ciphertext + c_len, &f_len);

        EVP_CIPHER_CTX_free(ctx);

        *len = c_len + f_len;
        return ciphertext;
    }

    unsigned char *Crypto::Aes256DecryptString(unsigned char *ciphertext, int *len, unsigned char *key) {

        // Opaque encryption, decryption ctx structures that libcrypto uses to record status of enc/dec operations
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

        auto *key_data = key;
        int key_data_len = (int) strlen(reinterpret_cast<const char *>(key_data));

        if (Aes256DecryptionInit(key_data, key_data_len, (unsigned char *) &_salt, ctx)) {
            log_error << "Couldn't initialize AES cipher";
            return {};
        }

        // Max ciphertext len for n bytes of plaintext is n + AES_BLOCK_SIZE -1 bytes
        int c_len = *len, f_len = 0, p_len = 0;
        auto *plaintext = static_cast<unsigned char *>(malloc(c_len));

        EVP_DecryptInit_ex(ctx, nullptr, nullptr, nullptr, nullptr);
        EVP_DecryptUpdate(ctx, plaintext, &p_len, ciphertext, c_len);
        p_len = *len;
        EVP_DecryptFinal(ctx, plaintext + c_len, len);
        p_len += *len;

        EVP_CIPHER_CTX_free(ctx);

        plaintext[p_len] = '\0';
        return plaintext;
    }

    int Crypto::Aes256EncryptionInit(unsigned char *key_data, int key_data_len, unsigned char *salt, EVP_CIPHER_CTX *ctx) {

        int i, nrounds = 5;
        unsigned char key[CRYPTO_AES256_KEY_SIZE], iv[CRYPTO_AES256_BLOCK_SIZE];

        // Gen key & IV for AES 256 CBC mode. A SHA1 digest is used to hash the supplied key material. nrounds is the number of times
        // we hash the material. More rounds are more secure but slower.
        i = EVP_BytesToKey(EVP_aes_256_gcm(), EVP_sha1(), salt, key_data, key_data_len, nrounds, key, iv);
        if (i != 32) {
            log_error << "Key size is " << i << " bits - should be 256 bits";
            return -1;
        }

        EVP_CIPHER_CTX_init(ctx);
        EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key, iv);

        return 0;
    }

    int Crypto::Aes256DecryptionInit(unsigned char *key_data, int key_data_len, unsigned char *salt, EVP_CIPHER_CTX *ctx) {

        int i, nrounds = 5;
        unsigned char key[CRYPTO_AES256_KEY_SIZE], iv[CRYPTO_AES256_BLOCK_SIZE];

        // Gen key & IV for AES 256 CBC mode. A SHA1 digest is used to hash the supplied key material. nrounds is the number of times,
        // we hash the material. More rounds are more secure but slower.
        i = EVP_BytesToKey(EVP_aes_256_gcm(), EVP_sha1(), salt, key_data, key_data_len, nrounds, key, iv);
        if (i != 32) {
            log_error << "Key size is " << i << " bits - should be 256 bits";
            return -1;
        }

        EVP_CIPHER_CTX_init(ctx);
        EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key, iv);

        return 0;
    }

    std::string Crypto::Base64Encode(const std::string &inputString) {
        std::istringstream in(inputString);
        std::ostringstream out;
        Poco::Base64Encoder encoder(out);
        Poco::StreamCopier::copyStream(in, encoder);
        encoder.close();
        return out.str();
    }

    std::string Crypto::Base64Decode(const std::string &encodedString) {
        std::istringstream in(encodedString);
        std::ostringstream out;
        Poco::Base64Decoder decoder(in);
        Poco::StreamCopier::copyStream(decoder, out);
        return out.str();
    }

    std::string Crypto::HexEncode(const std::string &inputString) {
        std::stringstream ss;
        ss.str("");
        Poco::HexBinaryEncoder encoder(ss);
        encoder << inputString;
        encoder.close();
        return ss.str();
    }

    std::string Crypto::HexEncode(unsigned char *hash, int size) {
        return HexEncode({(char *) hash, static_cast<size_t>(size)});
    }

    std::string Crypto::HexDecode(const std::string &hex) {
        std::stringstream ss;
        ss.str("");
        Poco::HexBinaryDecoder decoder(ss);
        ss << hex;
        std::stringstream ss1;
        ss1 << decoder.rdbuf();
        return ss1.str();
    }

    EVP_PKEY *Crypto::GenerateRsaKeys(unsigned int keyLength) {
        EVP_PKEY *pRSA = EVP_RSA_gen(keyLength);
        if (!pRSA) {
            log_error << "Could not generate RSA key, length: " << keyLength;
            return nullptr;
        }
        return pRSA;
    }

    std::string Crypto::GetRsaPublicKey(EVP_PKEY *pRSA) {

        BIO *bp = BIO_new(BIO_s_mem());
        PEM_write_bio_PUBKEY(bp, pRSA);

        int size;
        char *buf = (char *) malloc(CRYPTO_RSA_KEY_LINE_LENGTH);
        std::ostringstream sstream;
        do {
            size = BIO_gets(bp, buf, CRYPTO_RSA_KEY_LINE_LENGTH);
            sstream << buf;
        } while (size > 0);
        free(buf);

        return sstream.str();
    }

    std::string Crypto::GetRsaPrivateKey(EVP_PKEY *pRSA) {

        BIO *bp = BIO_new(BIO_s_mem());
        PEM_write_bio_PUBKEY(bp, pRSA);

        int size;
        char *buf = (char *) malloc(CRYPTO_RSA_KEY_LINE_LENGTH);
        std::ostringstream sstream;
        PEM_write_bio_PrivateKey(bp, pRSA, nullptr, nullptr, 0, nullptr, nullptr);
        do {
            size = BIO_gets(bp, buf, CRYPTO_RSA_KEY_LINE_LENGTH);
            sstream << buf;
        } while (size > 0);
        free(buf);

        return sstream.str();
    }

    std::string Crypto::RsaEncrypt(EVP_PKEY *keyPair, const std::string &in) {

        size_t outLen;
        auto inLen = static_cast<size_t>(in.length());
        auto bytes = reinterpret_cast<const unsigned char *>(in.c_str());

        EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(keyPair, nullptr);
        EVP_PKEY_encrypt_init(ctx);
        EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING);

        // Get output length
        if (EVP_PKEY_encrypt(ctx, nullptr, &outLen, bytes, inLen) <= 0) {
            log_error << "Could not get length of encrypted string, error: " << ERR_error_string(ERR_get_error(), nullptr);
        };

        auto *encrypt = (unsigned char *) OPENSSL_malloc(outLen);
        if (EVP_PKEY_encrypt(ctx, encrypt, &outLen, bytes, inLen) <= 0) {
            log_error << "Could not encrypt string, error: " << ERR_error_string(ERR_get_error(), nullptr);
        }
        EVP_PKEY_CTX_free(ctx);
        return {reinterpret_cast<const char *>(encrypt), static_cast<size_t>(outLen)};
    }

    std::string Crypto::RsaDecrypt(EVP_PKEY *keyPair, const std::string &in) {

        size_t outLen;
        int inLen = static_cast<int>(in.length());
        auto *bytes = (unsigned char *) in.c_str();

        EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(keyPair, nullptr);
        EVP_PKEY_decrypt_init(ctx);
        EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING);

        // Get output length
        if (EVP_PKEY_decrypt(ctx, nullptr, &outLen, bytes, inLen) <= 0) {
            log_error << "Could not get length of encrypted string, error: " << ERR_error_string(ERR_get_error(), nullptr);
        };

        auto *decrypt = (unsigned char *) OPENSSL_malloc(outLen);
        if (EVP_PKEY_decrypt(ctx, decrypt, &outLen, bytes, inLen) <= 0) {
            log_error << "Could not decrypt string, error: " << ERR_error_string(ERR_get_error(), nullptr);
        }
        EVP_PKEY_CTX_free(ctx);
        return {(char *) decrypt, outLen};
    }

}// namespace AwsMock::Core