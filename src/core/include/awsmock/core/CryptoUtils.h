//
// Created by vogje01 on 22/08/2022.
//

#ifndef AWS_MOCK_CORE_CRYPTO_UTILS_H
#define AWS_MOCK_CORE_CRYPTO_UTILS_H

// Standard C includes
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

// Standard C++ includes
#include <string>
#include <string_view>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <array>

// Openssl includes
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/aes.h>

// AwsMock includes
#include <awsmock/core/StringUtils.h>

// 64kB buffer
#define AWSMOCK_BUFFER_SIZE 4096

namespace AwsMock::Core {

  static const std::string _base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  /**
   * Cryptographic utilities like MD5 hash, SHA1, SHA256 etc.
   *
   * @author jens.vogt@opitz-consulting.com
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
     * AES 256 encryption
     *
     * @param plaintext input string
     * @param len plaintext length
     * @param key encryption key
     * @return encrypted string
     */
    static unsigned char* Aes256EncryptString(unsigned char* plaintext, int *len, const std::string &key);

    /**
     * AES 256 description
     *
     * @param ciphertext input string
     * @param len ciphertext length
     * @param key encryption key
     * @return decrypted string
     */
    static unsigned char* Aes256DecryptString(unsigned char* ciphertext, int *len, const std::string &key);

    /**
     * Base64 encoding.
     *
     * @param inputString input string
     * @return BASE64 encoded string.
     */
    static std::string Base64Encode(const std::string &inputString);

    /**
     * Base64 encoding.
     *
     * @param input input char array
     * @return BASE64 encoded string.
     */
    static std::string Base64Encode(unsigned char* input);

    /**
     * Base64 decoding.
     *
     * @param encodedString encoded input string
     * @return BASE64 decoded string.
     */
    static std::string Base64Decode(const std::string &encodedString);

    /**
     * Convert to hex string
     *
     * @param input input byte array
     * @return hex encoded string
     */
    static std::string HexEncode(std::array<unsigned char, EVP_MAX_MD_SIZE> input);

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

  private:

    /**
     * Create a 256 bit key and IV using the supplied key_data. salt can be added for taste. Fills in the encryption and decryption ctx objects and returns 0 on success.
     *
     * @param key_data key data
     * @param key_data_len length of key data
     * @param salt salt value
     * @param ctx openssl context
     */
    static int Aes256EncryptionInit(unsigned char *key_data, int key_data_len, unsigned char *salt, EVP_CIPHER_CTX *ctx);

    /**
     * Create a 256 bit key and IV using the supplied key_data. salt can be added for taste. Fills in the encryption and decryption ctx objects and returns 0 on success.
     *
     * @param key_data key data
     * @param key_data_len length of key data
     * @param salt salt value
     * @param ctx openssl context
     */
    static int Aes256DecryptionInit(unsigned char *key_data, int key_data_len, unsigned char *salt, EVP_CIPHER_CTX *ctx);
  };

  static inline bool IsBase64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
  }

} // namespace AwsMock::Core

#endif // AWS_MOCK_CORE_CRYPTO_UTILS_H
