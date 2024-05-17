//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/core/CryptoUtils.h>

namespace AwsMock::Core {

    unsigned int Crypto::_salt[] = {1214370622, 264849915};

    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string Crypto::GetMd5FromString(const std::string &content) {

        EVP_MD_CTX *context = EVP_MD_CTX_new();
        const EVP_MD *md = EVP_md5();
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;

        EVP_DigestInit(context, md);
        EVP_DigestUpdate(context, reinterpret_cast<const unsigned char *>(content.c_str()), content.length());
        EVP_DigestFinal(context, md_value, &md_len);
        EVP_MD_CTX_free(context);

        return HexEncode(md_value, static_cast<int>(md_len));
    }

    // TODO: Removed, until AWS uses openssl 3.0
    /*    std::string Crypto::AWSGetMd5FromString(const std::string &content) {

        struct aws_allocator *defaultAllocator = aws_default_allocator();
        Aws::Crt::ApiHandle apiHandle(defaultAllocator);
        Aws::Crt::Crypto::Hash md5 = Aws::Crt::Crypto::Hash::CreateMD5(defaultAllocator);

        Aws::Crt::ByteCursor input = aws_byte_cursor_from_c_str(content.c_str());

        int8_t output[Aws::Crt::Crypto::MD5_DIGEST_SIZE] = {0};
        Aws::Crt::ByteBuf outputBuf = Aws::Crt::ByteBufFromEmptyArray(reinterpret_cast<const uint8_t *>(output), sizeof(output));

        md5.Update(input);
        md5.Digest(outputBuf);

        Aws::Crt::ByteCursor outCursor = aws_byte_cursor_from_buf(&outputBuf);

        int8_t hexOut[Aws::Crt::Crypto::MD5_DIGEST_SIZE * 2] = {0};
        Aws::Crt::ByteBuf hexOutBuf = Aws::Crt::ByteBufFromEmptyArray(reinterpret_cast<const uint8_t *>(hexOut), sizeof(outputBuf) * 2 + 1);
        aws_hex_encode(&outCursor, &hexOutBuf);

        aws_cal_library_clean_up();

        std::string outStr((const char *) hexOutBuf.buffer, static_cast<size_t>(hexOutBuf.len));

        aws_byte_buf_clean_up(&outputBuf);
        aws_byte_buf_clean_up(&hexOutBuf);

        return outStr;
    }*/

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
        delete[] buffer;

        return HexEncode(md_value, static_cast<int>(md_len));
    }

    // TODO: Removed, until AWS uses openssl 3.0
    /*std::string Crypto::AwsGetMd5FromFile(const std::string &fileName) {

        char *buffer = new char[AWSMOCK_BUFFER_SIZE];

        struct aws_allocator *defaultAllocator = aws_default_allocator();
        Aws::Crt::ApiHandle apiHandle(defaultAllocator);
        Aws::Crt::Crypto::Hash md5 = Aws::Crt::Crypto::Hash::CreateMD5(defaultAllocator);

        int8_t output[Aws::Crt::Crypto::MD5_DIGEST_SIZE] = {0};
        Aws::Crt::ByteBuf outputBuf = Aws::Crt::ByteBufFromEmptyArray(reinterpret_cast<const uint8_t *>(output), sizeof(output));

        std::ifstream ifs(fileName, std::ios::binary);
        while (ifs.good()) {
            ifs.read(buffer, AWSMOCK_BUFFER_SIZE);
            md5.Update(aws_byte_cursor_from_c_str(buffer));
        }
        md5.Digest(outputBuf);
        ifs.close();

        Aws::Crt::ByteCursor outCursor = aws_byte_cursor_from_buf(&outputBuf);

        int8_t hexOut[Aws::Crt::Crypto::MD5_DIGEST_SIZE * 2] = {0};
        Aws::Crt::ByteBuf hexOutBuf = Aws::Crt::ByteBufFromEmptyArray(reinterpret_cast<const uint8_t *>(hexOut), sizeof(outputBuf) * 2 + 1);
        aws_hex_encode(&outCursor, &hexOutBuf);

        aws_cal_library_clean_up();

        std::string outStr((const char *) hexOutBuf.buffer, static_cast<size_t>(hexOutBuf.len));

        aws_byte_buf_clean_up(&outputBuf);
        aws_byte_buf_clean_up(&hexOutBuf);

        return outStr;
    }*/

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

        return HexEncode(md_value, static_cast<int>(md_len));
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

        // Finalize
        EVP_DigestFinal_ex(context, md_value, &md_len);
        EVP_MD_CTX_free(context);
        delete[] buffer;

        return HexEncode(md_value, static_cast<int>(md_len));
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

        return HexEncode(md_value, static_cast<int>(md_len));
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

        return HexEncode(hash.data(), static_cast<int>(hashLen));
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

        // Finalize
        EVP_DigestFinal_ex(context, md_value, &md_len);
        EVP_MD_CTX_free(context);
        delete[] buffer;

        return HexEncode(md_value, static_cast<int>(md_len));
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

    void Crypto::Aes256EncryptFile(const std::string &filename, unsigned char *key) {

        // "opaque" encryption, decryption ctx structures that libcrypto uses to record status of enc/dec operations
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

        auto *key_data = key;
        int key_data_len = (int) strlen(reinterpret_cast<const char *>(key_data));

        if (Aes256EncryptionInit(key_data, key_data_len, (unsigned char *) &_salt, ctx)) {
            log_error << "Couldn't initialize AES256 cipher";
        }

        std::string outFilename = filename + ".aes256";
        std::ifstream input_file(filename, std::ios::binary);
        std::ofstream output_file(outFilename, std::ios::binary);
        int outFileLen = 0;

        // max ciphertext len for n bytes of plaintext is n + AES_BLOCK_SIZE -1 bytes
        char *in_buf = new char[AWSMOCK_BUFFER_SIZE];
        char *out_buf = new char[AWSMOCK_BUFFER_SIZE + AES_BLOCK_SIZE];

        // Allows reusing of 'ctx' for multiple encryption cycles
        EVP_EncryptInit_ex(ctx, nullptr, nullptr, nullptr, nullptr);

        int count = 0;
        while (!input_file.eof()) {
            input_file.read(in_buf, AWSMOCK_BUFFER_SIZE);
            std::streamsize dataSize = input_file.gcount();
            if (1 == EVP_EncryptUpdate(ctx, (unsigned char *) out_buf, &outFileLen, (const unsigned char *) in_buf, (int) dataSize)) {
                output_file.write(out_buf, outFileLen);
                log_trace << "AES256 encryption of file, written: " << outFileLen;
            } else {
                log_error << "Encryption failed after " << count << " chunk";
                break;
            }
        }
        EVP_EncryptFinal_ex(ctx, (unsigned char *) out_buf, &outFileLen);
        EVP_CIPHER_CTX_free(ctx);
        input_file.close();
        output_file.close();
        free(in_buf);
        free(out_buf);

        Core::FileUtils::MoveTo(outFilename, filename);
    }

    void Crypto::Aes256DecryptFile(const std::string &filename, std::string &outFilename, unsigned char *key) {

        // "opaque" encryption, decryption ctx structures that libcrypto uses to record status of enc/dec operations
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

        auto *key_data = key;
        int key_data_len = (int) strlen(reinterpret_cast<const char *>(key_data));

        if (Aes256DecryptionInit(key_data, key_data_len, (unsigned char *) &_salt, ctx)) {
            log_error << "Couldn't initialize AES256 cipher";
        }

        outFilename = filename + ".plain";
        std::ifstream input_file(filename, std::ios::binary);
        std::ofstream output_file(outFilename, std::ios::binary);
        int outFileLen = 0;

        // max ciphertext len for n bytes of plaintext is n + AES_BLOCK_SIZE -1 bytes
        char *in_buf = new char[AWSMOCK_BUFFER_SIZE];
        char *out_buf = new char[AWSMOCK_BUFFER_SIZE + AES_BLOCK_SIZE];

        // Allows reusing of 'ctx' for multiple encryption cycles
        EVP_DecryptInit_ex(ctx, nullptr, nullptr, nullptr, nullptr);

        int count = 0;
        while (!input_file.eof()) {
            input_file.read(in_buf, AWSMOCK_BUFFER_SIZE);
            std::streamsize dataSize = input_file.gcount();
            if (1 == EVP_DecryptUpdate(ctx, (unsigned char *) out_buf, &outFileLen, (const unsigned char *) in_buf, (int) dataSize)) {
                output_file.write(out_buf, outFileLen);
                log_trace << "AES256 decryption of file, written: " << outFileLen;
            } else {
                log_error << "Decryption failed after " << count << " chunk";
                break;
            }
        }
        EVP_DecryptFinal_ex(ctx, (unsigned char *) out_buf, &outFileLen);
        EVP_CIPHER_CTX_free(ctx);
        input_file.close();
        output_file.close();
        free(in_buf);
        free(out_buf);
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

    /*std::string Crypto::Base64Encode(unsigned char const *buf, unsigned int bufLen) {
        std::string ret;
        int i = 0;
        int j = 0;
        unsigned char char_array_3[3];
        unsigned char char_array_4[4];

        while (bufLen--) {
            char_array_3[i++] = *(buf++);
            if (i == 3) {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;

                for (i = 0; (i < 4); i++)
                    ret += base64_chars[char_array_4[i]];
                i = 0;
            }
        }

        if (i) {
            for (j = i; j < 3; j++)
                char_array_3[j] = '\0';

            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (j = 0; (j < i + 1); j++)
                ret += base64_chars[char_array_4[j]];

            while ((i++ < 3))
                ret += '=';
        }

        return ret;
    }

    unsigned char *Crypto::Base64Decode(std::string const &encoded_string) {
        int in_len = encoded_string.size();
        int i = 0;
        int j = 0;
        int in_ = 0;
        unsigned char char_array_4[4], char_array_3[3];
        std::vector<unsigned char> ret;

        while (in_len-- && (encoded_string[in_] != '=') && IsBase64(encoded_string[in_])) {
            char_array_4[i++] = encoded_string[in_];
            in_++;
            if (i == 4) {
                for (i = 0; i < 4; i++)
                    char_array_4[i] = base64_chars.find(char_array_4[i]);

                char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                for (i = 0; (i < 3); i++)
                    ret.push_back(char_array_3[i]);
                i = 0;
            }
        }

        if (i) {
            for (j = i; j < 4; j++)
                char_array_4[j] = 0;

            for (j = 0; j < 4; j++)
                char_array_4[j] = base64_chars.find(char_array_4[j]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
        }

        return ret.data();
    }*/

    std::string Crypto::Base64Decode(const std::string &encodedString) {
        std::istringstream in(encodedString);
        std::ostringstream out;
        Poco::Base64Decoder decoder(in);
        Poco::StreamCopier::copyStream(decoder, out);
        decoder.clear();
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
        char *out = OPENSSL_buf2hexstr(hash, size);
        auto sout = Poco::toLower<std::string>({out});
        sout = Poco::replace<std::string>(sout, ":", "");
        free(out);
        return {sout};
    }

    unsigned char *Crypto::HexDecode(const std::string &hex) {
        long len;
        unsigned char *out = OPENSSL_hexstr2buf(hex.data(), &len);
        out[len] = '\0';
        return out;
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

    EVP_PKEY *Crypto::ReadRsaPrivateKey(const std::string &inKey) {

        BIO *bo = BIO_new(BIO_s_mem());
        BIO_write(bo, inKey.c_str(), static_cast<int>(inKey.length()));

        EVP_PKEY *pKey = nullptr;
        PEM_read_bio_PrivateKey(bo, &pKey, nullptr, nullptr);

        BIO_free(bo);
        return pKey;
    }

    EVP_PKEY *Crypto::ReadRsaPublicKey(const std::string &publicKey) {

        EVP_PKEY *pKey = nullptr;
        BIO *bo2 = BIO_new(BIO_s_mem());
        BIO_write(bo2, publicKey.c_str(), static_cast<int>(publicKey.length()));
        PEM_read_bio_PUBKEY(bo2, &pKey, nullptr, nullptr);
        BIO_free(bo2);

        return pKey;
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