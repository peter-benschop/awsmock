//
// Created by vogje01 on 22/08/2022.
//

#ifndef AWS_MOCK_CORE_CRYPTO_UTILS_H
#define AWS_MOCK_CORE_CRYPTO_UTILS_H

// Standard C includes
#include <fcntl.h>
#ifndef _WIN32
#include <sys/mman.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>

// Standard C++ includes
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <string_view>

// Openssl includes
#include <openssl/aes.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/md5.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>

// AwsMock includes
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/RandomUtils.h>
#include <awsmock/core/StringUtils.h>

// 64kB buffer
#define AWSMOCK_BUFFER_SIZE 4096

// Poco
#include <Poco/Base64Decoder.h>
#include <Poco/Base64Encoder.h>
#include <Poco/HexBinaryDecoder.h>
#include <Poco/HexBinaryEncoder.h>
#include <Poco/StreamCopier.h>

#define CRYPTO_RSA_KEY_LEN_4096 4096
#define CRYPTO_RSA_KEY_LEN_2048 2048
#define CRYPTO_RSA_KEY_LEN_1024 1024
#define CRYPTO_RSA_KEY_EXP 65535
#define CRYPTO_RSA_KEY_LINE_LENGTH 64

#define CRYPTO_AES256_KEY_SIZE 32
#define CRYPTO_AES256_BLOCK_SIZE 16

namespace AwsMock::Core {

    static const std::string _base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    /**
     * Cryptographic utilities like MD5 hash, SHA1, SHA256 etc.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Crypto {

      public:

        /**
         * Returns the MD5 hash of a string.
         *
         * @param content string to hash
         * @return MD5 hash of the given string
         */
        static std::string GetMd5FromString(const std::string &content);

        /**
         * Returns the MD5 hash of a file.
         *
         * @param fileName file name to hash
         * @return MD5 hash of the given file
         */
        static std::string GetMd5FromFile(const std::string &fileName);

        /**
         * Returns the SHA1 hash of a string.
         *
         * @param content string to hash
         * @return SHA1 hash of the given string
         */
        static std::string GetSha1FromString(const std::string &content);

        /**
         * Returns the SHA1 hash of a file.
         *
         * @param fileName file name to hash
         * @return SHA1 hash of the given file
         */
        static std::string GetSha1FromFile(const std::string &fileName);

        /**
         * Returns the SHA256 hash of a string.
         *
         * @param content string to hash
         * @return SHA256 hash of the given string
         */
        static std::string GetSha256FromString(const std::string &content);

        /**
         * Returns the SHA256 hash of a file.
         *
         * @param fileName file name to hash
         * @return SHA256 hash of the given file
         */
        static std::string GetSha256FromFile(const std::string &fileName);

        /**
         * Returns the hex encoded SHA256 hash of a string.
         *
         * @param key string for hashing
         * @param content string to hash
         * @return SHA256 hash of the given string
         */
        static std::string GetHmacSha256FromString(const std::string &key, const std::string &content);

        /**
         * Returns the hex encoded SHA256 hash of a string.
         *
         * @param key byte array for hashing
         * @param content string to hash
         * @return SHA256 hash of the given string
         */
        static std::string GetHmacSha256FromString(const std::array<unsigned char, EVP_MAX_MD_SIZE> &key, const std::string &content);

        /**
         * Returns the SHA256 hash of a string.
         *
         * @param key string for hashing
         * @param msg string to hash
         * @return SHA256 hash of the given string
         */
        static std::array<unsigned char, EVP_MAX_MD_SIZE> GetHmacSha256FromStringRaw(const std::string &key, const std::string &msg);

        /**
         * Returns the SHA256 hash of a string.
         *
         * @param key byte array for hashing
         * @param msg string to hash
         * @return SHA256 hash of the given string
         */
        static std::array<unsigned char, EVP_MAX_MD_SIZE> GetHmacSha256FromStringRaw(const std::array<unsigned char, EVP_MAX_MD_SIZE> &key, const std::string &msg);

        /**
         * Creates a AES 256 encryption key.
         *
         * @param key 265bit key material
         * @param iv iv
         */
        static void CreateAes256Key(unsigned char *key, unsigned char *iv);

        /**
         * @brief AES 256 encryption
         *
         * @param plaintext input string
         * @param len plaintext length
         * @param key encryption key
         * @return encrypted string
         */
        static unsigned char *Aes256EncryptString(unsigned char *plaintext, int *len, unsigned char *key);

        /**
         * @brief AES256 description
         *
         * @param ciphertext input string
         * @param len ciphertext length
         * @param key encryption key
         * @return decrypted string
         */
        static unsigned char *Aes256DecryptString(unsigned char *ciphertext, int *len, unsigned char *key);

        /**
         * @brief AES256 encryption of a file
         *
         * <p>
         * The original plaintext file will be replaced by the encrypted file.
         * </p>
         *
         * @param filename input file name
         * @param key encryption key
         * @return encrypted string
         */
        static void Aes256EncryptFile(const std::string &filename, unsigned char *key);

        /**
         * @brief AES256 description of a file.
         *
         * <p>
         * The actual file will stay encrypted. Outfile must be deleted after send to client.
         * </p>
         *
         * @param filename input file name
         * @param outFilename output filename
         * @param key encryption key
         * @return decrypted string
         */
        static void Aes256DecryptFile(const std::string &filename, std::string &outFilename, unsigned char *key);

        /**
         * Base64 encoding.
         *
         * @param inputString input string
         * @return BASE64 encoded string.
         */
        static std::string Base64Encode(const std::string &inputString);

        /**
         * Base64 decoding.
         *
         * @param encodedString encoded input string
         * @return BASE64 decoded string.
         */
        static std::string Base64Decode(const std::string &encodedString);

        //static unsigned char *Base64Decode(std::string const &encoded_string);

        //static std::string Base64Encode(unsigned char const *buf, unsigned int bufLen);

        /**
         * Convert to hex string
         *
         * @param input input byte array
         * @return hex encoded string
         */
        static std::string HexEncode(const std::string &input);

        /**
         * Convert to hex string
         *
         * @param hash input char array
         * @param size input char length
         * @return hex encoded string
         */
        static std::string HexEncode(unsigned char *hash, int size);

        /**
         * Decodes a hex string to an unsigned char array.
         *
         * @param hex hex string
         * @return unsigned char array.
         */
        static unsigned char *HexDecode(const std::string &hex);

        /**
         * Generate a RSA key pair of the given length.
         *
         * @param keyLength key length
         * @return RSA key pair.
         */
        static EVP_PKEY *GenerateRsaKeys(unsigned int keyLength);

        /**
         * Converts the public key to a string.
         *
         * @param pRSA pointer to RSA key pair
         */
        static std::string GetRsaPublicKey(EVP_PKEY *pRSA);

        /**
         * Converts the private key to a string.
         *
         * @param pRSA pointer to RSA key pair
         */
        static std::string GetRsaPrivateKey(EVP_PKEY *pRSA);

        /**
         * Read an EVP_PKEY from a string.
         *
         * @param privateKey key as string
         * @return *EVP_PKEY
         */
        static EVP_PKEY *ReadRsaPrivateKey(const std::string &privateKey);

        /**
         * Read an EVP_PKEY from a string.
         *
         * @param publicKey key as string
         * @return *EVP_PKEY
         */
        static EVP_PKEY *ReadRsaPublicKey(const std::string &publicKey);

        /**
         * Encrypt a string using RSA encryption.
         *
         * <p>
         * The output string will be Base64 encoded.
         * </p>
         *
         * @param keyPair RSA keypair.
         * @param in ini string
         * @return Base64 encoded string
         */
        static std::string RsaEncrypt(EVP_PKEY *keyPair, const std::string &in);

        /**
         * Decrypts a string using RSA encryption.
         *
         * <p>
         * The input string must be Base64 encoded.
         * </p>
         *
         * @param keyPair RSA keypair.
         * @param in ini string
         * @return Base64 encoded string
         */
        static std::string RsaDecrypt(EVP_PKEY *keyPair, const std::string &in);

      private:

        /**
         * Create a 256 bit key and IV using the supplied key_data. salt can be added for taste. Fills in the encryption and decryption ctx objects and returns 0 on success.
         *
         * @param key_data key data
         * @param key_data_len length of key data
         * @param salt salt value
         * @param ctx openssl model
         */
        static int Aes256EncryptionInit(unsigned char *key_data, int key_data_len, unsigned char *salt, EVP_CIPHER_CTX *ctx);

        /**
         * Create a 256 bit key and IV using the supplied key_data. salt can be added for taste. Fills in the encryption and decryption ctx objects and returns 0 on success.
         *
         * @param key_data key data
         * @param key_data_len length of key data
         * @param salt salt value
         * @param ctx openssl model
         */
        static int Aes256DecryptionInit(unsigned char *key_data, int key_data_len, unsigned char *salt, EVP_CIPHER_CTX *ctx);

        static unsigned int _salt[];
    };

    static inline bool IsBase64(unsigned char c) {
        return (isalnum(c) || (c == '+') || (c == '/'));
    }

}// namespace AwsMock::Core

#endif// AWS_MOCK_CORE_CRYPTO_UTILS_H
