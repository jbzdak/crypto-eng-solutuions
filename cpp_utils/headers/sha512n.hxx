//
// Created by jb on 8/6/17.
//

#ifndef CRYPTO_BOOK_EXCERCISES_SHA512N_HXX_H
#define CRYPTO_BOOK_EXCERCISES_SHA512N_HXX_H

#include "utils.h"
#include "botan/sha2_64.h"
#include <memory>
template<size_t n>
class SHA512n: public Botan::Buffered_Computation{

public:

    SHA512n(): sha(std::make_unique<Botan::SHA_512>()){}

    size_t output_length() const override {
        return n;
    }

    virtual ~SHA512n() override {}

private:

    std::unique_ptr<Botan::SHA_512> sha;

    void add_data(const Botan::byte *input, size_t length) override {
        sha->update(input, length);
    }

    void final_result(Botan::byte *out) override {

        BytesVector result(sha->output_length(), 0);

        sha->final(result.data());

        std::copy_n(result.data(), n, out);

    }

};


#endif //CRYPTO_BOOK_EXCERCISES_SHA512N_HXX_H
