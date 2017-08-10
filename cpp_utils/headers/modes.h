
//
// Created by jb on 7/29/17.
//

#ifndef CRYPTO_BOOK_EXCERCISES_MODES_H_H
#define CRYPTO_BOOK_EXCERCISES_MODES_H_H

#include "utils.h"

#include "botan/block_cipher.h"
#include <memory>
#include <cassert>


class IPadding{

public:

    virtual BytesVector pad(const BytesVector& input, int block_size) =0;
    virtual BytesVector remove_padding(const BytesVector& padded, int block_size) =0;

};

class NoopPaddng: public IPadding{
    virtual BytesVector pad(const BytesVector& input, int block_size){
        assert(input.size() % block_size == 0);
        return input;
    }

    virtual BytesVector remove_padding(const BytesVector& padded, int block_size){
        return padded;
    }
};

class BlockMode{

protected:

    std::unique_ptr<Botan::BlockCipher> cipher;
    std::unique_ptr<IPadding> padding;
    BytesVector key;
    BytesVector iv;

public:

    BlockMode(std::unique_ptr<Botan::BlockCipher> cipher, std::unique_ptr<IPadding> padding):
            cipher(std::move(cipher)), padding(std::move(padding)){}

    void start(const BytesVector& key, const BytesVector& iv){
        this->key = key;
        this->iv = iv;
        this->cipher->set_key(key.data(), key.size());
    }

    virtual size_t block_size(){
        return this->cipher->block_size();
    }

    virtual Botan::Key_Length_Specification key_size(){
        return this->cipher->key_spec();
    }

    virtual BytesVector encrypt_data(const BytesVector& data) = 0;
    virtual BytesVector decrypt_data(const BytesVector& data) = 0;


};

class ECBMode: public BlockMode {

public:
    ECBMode(std::unique_ptr<Botan::BlockCipher> cipher, std::unique_ptr<IPadding> padding);

public:
    virtual BytesVector encrypt_data(const BytesVector& data);
    virtual BytesVector decrypt_data(const BytesVector& data);

};


class CBCMode: public BlockMode {

public:
    CBCMode(std::unique_ptr<Botan::BlockCipher> cipher, std::unique_ptr<IPadding> padding);

public:
    virtual BytesVector encrypt_data(const BytesVector& data);
    virtual BytesVector decrypt_data(const BytesVector& data);

};
#endif //CRYPTO_BOOK_EXCERCISES_MODES_H_H
