//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/core/CryptoUtils.h>

namespace AwsMock::Core {

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
        return HexEncode(hash);
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

    unsigned char *Crypto::Aes256EncryptString(unsigned char *plaintext, int *len, const std::string &key) {

        // "opaque" encryption, decryption ctx structures that libcrypto uses to record status of enc/dec operations
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

        unsigned int salt[] = {12345, 54321};
        auto *key_data = (unsigned char *) key.c_str();
        int key_data_len = (int) strlen(reinterpret_cast<const char *>(key_data));

        if (Aes256EncryptionInit(key_data, key_data_len, (unsigned char *) &salt, ctx)) {
            printf("Couldn't initialize AES cipher\n");
            return {};
        }

        /* max ciphertext len for a n bytes of plaintext is n + AES_BLOCK_SIZE -1 bytes */
        int c_len = *len + AES_BLOCK_SIZE, f_len = 0;
        auto *ciphertext = static_cast<unsigned char *>(malloc(c_len));

        // Allows reusing of 'ctx' for multiple encryption cycles
        EVP_EncryptInit_ex(ctx, nullptr, nullptr, nullptr, nullptr);
        EVP_EncryptUpdate(ctx, ciphertext, &c_len, plaintext, *len);
        EVP_EncryptFinal_ex(ctx, ciphertext + c_len, &f_len);

        EVP_CIPHER_CTX_free(ctx);

        *len = c_len + f_len;
        return ciphertext;
    }

    unsigned char *Crypto::Aes256DecryptString(unsigned char *ciphertext, int *len, const std::string &key) {

        // "opaque" encryption, decryption ctx structures that libcrypto uses to record status of enc/dec operations
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

        unsigned int salt[] = {12345, 54321};
        auto *key_data = (unsigned char *) key.c_str();
        int key_data_len = (int) strlen(reinterpret_cast<const char *>(key_data));

        if (Aes256DecryptionInit(key_data, key_data_len, (unsigned char *) &salt, ctx)) {
            printf("Couldn't initialize AES cipher\n");
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
        unsigned char key[32], iv[32];

        /*
         * Gen key & IV for AES 256 CBC mode. A SHA1 digest is used to hash the supplied key material.
         * nrounds is the number of times the we hash the material. More rounds are more secure but
         * slower.
         */
        i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, key_data, key_data_len, nrounds, key, iv);
        if (i != 32) {
            printf("Key size is %d bits - should be 256 bits\n", i);
            return -1;
        }

        EVP_CIPHER_CTX_init(ctx);
        EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

        return 0;
    }

    int Crypto::Aes256DecryptionInit(unsigned char *key_data, int key_data_len, unsigned char *salt, EVP_CIPHER_CTX *ctx) {

        int i, nrounds = 5;
        unsigned char key[32], iv[32];

        /*
         * Gen key & IV for AES 256 CBC mode. A SHA1 digest is used to hash the supplied key material.
         * nrounds is the number of times, we hash the material. More rounds are more secure but
         * slower.
         */
        i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, key_data, key_data_len, nrounds, key, iv);
        if (i != 32) {
            printf("Key size is %d bits - should be 256 bits\n", i);
            return -1;
        }

        EVP_CIPHER_CTX_init(ctx);
        EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

        return 0;
    }

    std::string Crypto::Base64Encode(const std::string &inputString) {
        std::string out;

        int val = 0, valb = -6;
        for (unsigned char c: inputString) {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0) {
                out.push_back(_base64Chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6)
            out.push_back(_base64Chars[((val << 8) >> (valb + 8)) & 0x3F]);
        while (out.size() % 4)
            out.push_back('=');
        return out;
    }

    std::string Crypto::Base64Encode(unsigned char *input) {
        std::string out;

        int val = 0, valb = -6;
        for (unsigned char *c = input; c != input + strlen(reinterpret_cast<const char *>(input)); c++) {
            val = (val << 8) + *c;
            valb += 8;
            while (valb >= 0) {
                out.push_back(_base64Chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6)
            out.push_back(_base64Chars[((val << 8) >> (valb + 8)) & 0x3F]);
        while (out.size() % 4)
            out.push_back('=');
        return out;
    }

    std::string Crypto::Base64Decode(const std::string &encodedString) {

        size_t in_len = encodedString.size();
        int i = 0;
        int j = 0;
        int in_ = 0;
        unsigned char char_array_4[4], char_array_3[3];
        std::string ret;

        while (in_len-- && (encodedString[in_] != '=') && IsBase64(encodedString[in_])) {
            char_array_4[i++] = encodedString[in_];
            in_++;
            if (i == 4) {
                for (i = 0; i < 4; i++)
                    char_array_4[i] = _base64Chars.find((char) char_array_4[i]);

                char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                for (i = 0; (i < 3); i++)
                    ret += (char) char_array_3[i];
                i = 0;
            }
        }

        if (i) {
            for (j = i; j < 4; j++)
                char_array_4[j] = 0;

            for (j = 0; j < 4; j++)
                char_array_4[j] = _base64Chars.find((char) char_array_4[j]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (j = 0; (j < i - 1); j++)
                ret += (char) char_array_3[j];
        }

        return ret;
    }

    std::string Crypto::HexEncode(const std::array<unsigned char, EVP_MAX_MD_SIZE> hash) {
        std::stringstream ss;
        for (unsigned char i: hash) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
        }
        return {ss.str(), 0, hash.size()};
    }

    std::string Crypto::HexEncode(const std::string &hash) {
        return HexEncode((unsigned char *) hash.c_str(), (int) hash.length());
    }

    std::string Crypto::HexEncode(unsigned char *hash, int size) {
        std::stringstream ss;
        for (int i = 0; i < size; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }
        return {ss.str()};
    }

    EVP_PKEY *Crypto::GenerateRsaKeys(unsigned int keyLength) {
        EVP_PKEY *pRSA = EVP_RSA_gen(keyLength);
        if (!pRSA) {
            log_error << "Could not generate RSA key, length:" << keyLength;
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

    std::string Crypto::RsaEncrypt(EVP_PKEY *keyPair, const std::string &in) {

        EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(keyPair, nullptr);
        EVP_PKEY_encrypt_init(ctx);
        EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING);

        size_t outLen;
        if (EVP_PKEY_encrypt(ctx, nullptr, &outLen, reinterpret_cast<const unsigned char *>(in.c_str()), in.length()) < 0) {
            log_error << "Could not get length of encrypted string";
        };

        auto *encrypt = (unsigned char *) OPENSSL_malloc(outLen);
        if (EVP_PKEY_encrypt(ctx, encrypt, &outLen, reinterpret_cast<const unsigned char *>(in.c_str()), in.length()) < 0) {
            log_error << "Could not encrypt string";
        }
        EVP_PKEY_CTX_free(ctx);
        encrypt[outLen] = '0';
        return Base64Encode({reinterpret_cast<const char *>(encrypt), outLen});
    }

    std::string Crypto::RsaDecrypt(EVP_PKEY *keyPair, const std::string &in) {

        std::string inString = Base64Decode(in);
        auto *bytes = reinterpret_cast<const unsigned char *>(inString.c_str());

        EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(keyPair, nullptr);
        EVP_PKEY_decrypt_init(ctx);
        EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING);

        size_t outLen;
        if (EVP_PKEY_decrypt(ctx, nullptr, &outLen, bytes, inString.length()) < 0) {
            log_error << "Could not get length of encrypted string";
        };

        auto *decrypt = (unsigned char *) OPENSSL_malloc(outLen);
        if (EVP_PKEY_decrypt(ctx, decrypt, &outLen, bytes, inString.length()) < 0) {
            log_error << "Could not decrypt string";
        }
        EVP_PKEY_CTX_free(ctx);
        decrypt[outLen] = '\0';
        return {reinterpret_cast<const char *>(decrypt)};
    }

}// namespace AwsMock::Core