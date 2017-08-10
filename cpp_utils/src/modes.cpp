//
// Created by jb on 7/29/17.
//

#include <memory>
#include <cassert>

#include "botan/block_cipher.h"

#include "modes.h"



BytesVector ECBMode::encrypt_data(const BytesVector &data) {
    BytesVector response(data.size(), 0);

    const size_t bs = cipher->block_size();
    for (size_t ii=0; ii < (data.size() / bs); ii++){
        size_t block_start = ii*bs;
        cipher->encrypt(&data[block_start], &response[block_start]);
    }
    return response;

}

BytesVector ECBMode::decrypt_data(const BytesVector &data) {
    BytesVector response(data.size(), 0);

    const size_t bs = cipher->block_size();
    for (size_t ii=0; ii < (data.size() / bs); ii++){
        size_t block_start = ii*bs;
        cipher->decrypt(&data[block_start], &response[block_start]);
    }
    return response;
}

ECBMode::ECBMode(std::unique_ptr<Botan::BlockCipher> cipher, std::unique_ptr<IPadding> padding)
        :BlockMode(std::move(cipher), std::move(padding)) {}

CBCMode::CBCMode(std::unique_ptr<Botan::BlockCipher> cipher, std::unique_ptr<IPadding> padding)
        :BlockMode(std::move(cipher), std::move(padding)) {}

BytesVector CBCMode::encrypt_data(const BytesVector &data) {

    const size_t bs = cipher->block_size();
    BytesVector lastBlockEncrypted = this->iv;
    BytesVector currentBlockPlaintext(bs, 0);

    BytesVector response(data.size(), 0);

    for (size_t ii=0; ii < (data.size() / bs); ii++){
        size_t block_start = ii*bs;

        std::copy_n(data.begin() + block_start, bs, currentBlockPlaintext.begin());

        elementwise_xor(currentBlockPlaintext, lastBlockEncrypted, currentBlockPlaintext);

        cipher->encrypt(currentBlockPlaintext.data(), lastBlockEncrypted.data());

        std::copy_n(lastBlockEncrypted.begin(), bs, response.begin() + block_start);
    }

    return response;
}

BytesVector CBCMode::decrypt_data(const BytesVector &data) {
    const size_t bs = cipher->block_size();
    BytesVector lastBlockEncrypted = this->iv;
    BytesVector currentBlockEncrypted(bs, 0);
    BytesVector currentBlockDecrypted(bs, 0);
    BytesVector response(data.size(), 0);

    for (size_t ii=0; ii < (data.size() / bs); ii++) {
        size_t block_start = ii * bs;

        std::copy_n(data.begin() + block_start, bs, currentBlockEncrypted.begin());

        cipher->decrypt(currentBlockEncrypted.data(), currentBlockDecrypted.data());

        elementwise_xor(currentBlockDecrypted, lastBlockEncrypted, currentBlockDecrypted);
        std::copy_n(currentBlockDecrypted.begin(), bs, response.begin() + block_start);

        std::swap(lastBlockEncrypted, currentBlockEncrypted);
    }

    return response;
}


