//
// Created by jb on 7/29/17.
//

#include "utils.h"
#include "modes.h"
#include "botan/aes.h"
#include "botan/rng.h"
#define BOOST_TEST_MODULE test module name
#include <boost/test/included/unit_test.hpp>



template<typename ModeCreator>
class BlockModeTests{

public:

    BlockModeTests(ModeCreator c): mode(c()), generator(Botan::RandomNumberGenerator::make_rng()) {
        key.assign(mode->key_size().maximum_keylength(), 0);
        iv.assign(mode->block_size(), 0);
        generator->randomize(key.data(), mode->key_size().maximum_keylength());
        generator->randomize(iv.data(), mode->block_size());
    }

    std::unique_ptr<BlockMode> mode;

    BytesVector key;
    BytesVector iv;

    std::unique_ptr<Botan::RandomNumberGenerator> generator;

    void test_input_of_given_size(size_t input_size){
        mode->start(key, iv);
        BytesVector plaintext(input_size, 0);
        generator->randomize(plaintext.data(), input_size);
        BytesVector encrypted =  mode->encrypt_data(plaintext);

        BOOST_CHECK(plaintext == mode->decrypt_data(encrypted));
    }

    void test_one_block() {
        for (size_t ii = 0; ii < 100; ii++) {
           test_input_of_given_size(mode->block_size());
        }
    }

    void test_two_blocks(){
        test_input_of_given_size(mode->block_size()*2);
    }

    void test_longer_input(){
        test_input_of_given_size(mode->block_size()*100);
    }

    void test_multiple_encryptions(){
        test_input_of_given_size(mode->block_size());
        test_input_of_given_size(mode->block_size());
        test_input_of_given_size(mode->block_size());
        test_input_of_given_size(mode->block_size());
        test_input_of_given_size(mode->block_size());
    }


};

template <typename ModeCreator>
static void do_tests(ModeCreator c){
    BOOST_TEST_MESSAGE("test_one_block");
    BlockModeTests<ModeCreator>(c).test_one_block();
    BOOST_TEST_MESSAGE("test_two_blocks");
    BlockModeTests<ModeCreator>(c).test_two_blocks();
    BOOST_TEST_MESSAGE("test_longer_input");
    BlockModeTests<ModeCreator>(c).test_longer_input();
    BOOST_TEST_MESSAGE("test_multiple_encryptions");
    BlockModeTests<ModeCreator>(c).test_multiple_encryptions();
}


BOOST_AUTO_TEST_CASE( test_two_block_ecb )
{
    ECBMode mode(std::make_unique<Botan::AES_256>(), std::make_unique<NoopPaddng>());
    BytesVector key = read_from_string("80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01", 32);
    BytesVector message = read_from_string("29 6C 93 FD F4 99 AA EB 41 94 BA BC 2E 63 56 1D 29 6C 93 FD F4 99 AA EB 41 94 BA BC 2E 63 56 1D", 32);

    mode.start(key, BytesVector());

    BytesVector expected = read_from_string("80 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 80 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1");

    BytesVector result = mode.encrypt_data(message);
    std::cout << result << std::endl;
    BOOST_CHECK( result == expected );
}

BOOST_AUTO_TEST_CASE( test_ecb ){
    auto creator = [](){
        return std::make_unique<ECBMode>(std::make_unique<Botan::AES_256>(), std::make_unique<NoopPaddng>());
    };
    do_tests(creator);
}


BOOST_AUTO_TEST_CASE( test_cbc )
{    auto creator = [](){
        return std::make_unique<CBCMode>(std::make_unique<Botan::AES_256>(), std::make_unique<NoopPaddng>());
    };
    do_tests(creator);
}

BOOST_AUTO_TEST_CASE( test_xor )
{

    std::unique_ptr<Botan::RandomNumberGenerator> generator(Botan::RandomNumberGenerator::make_rng());
    BytesVector x1(4, 0);
    BytesVector x2(4, 0);
    generator->randomize(x1.data(), 4);
    generator->randomize(x2.data(), 4);
    BytesVector result(4, 0), x1Copy=x1;
    BOOST_CHECK(x1Copy == x1);
    for (size_t ii=0; ii < 100; ii++){
        elementwise_xor(x1, x2, result);
        elementwise_xor(x1, x2, x1);
        for (size_t jj=0; jj < 4; jj++){
            BOOST_CHECK(result[jj] == x1Copy[jj]^x2[jj]);
        }
        BOOST_CHECK(result == x1);
    }

}


BOOST_AUTO_TEST_CASE( test_cbc_encryption ){
    BytesVector key = read_from_string("80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01", 32);
    BytesVector iv = read_from_string("87 F3 48 FF 79 B8 11 AF 38 57 D6 71 8E 5F 0F 91", 16);
    BytesVector data = read_from_string("7C 3D 26 F7 73 77 63 5A 5E 43 E9 B5 CC 5D 05 92 6E 26 FF C5 22 0D C7 D4 05 F1 70 86 70 E6 E0 17", 32);
    BytesVector expected = read_from_string("0xbc 0x5b 0xe7 0xe6 0xf 0x9d 0x30 0x27 0xa7 0x42 0x30 0x1b 0x22 0x42 0x7d 0xd7 0xc4 0x6c 0xd8 0x7b 0xff 0x30 0x9b 0x0 0x8f 0xba 0x18 0x85 0x68 0x4d 0x16 0x3b", 32);

    CBCMode mode(std::make_unique<Botan::AES_256>(), std::make_unique<NoopPaddng>());

    mode.start(key, iv);
    BytesVector result = mode.encrypt_data(data);

    BOOST_CHECK( expected == result);

}


BOOST_AUTO_TEST_CASE( test_cbc_decryption ){
    BytesVector key = read_from_string("80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01", 32);
    BytesVector iv = read_from_string("87 F3 48 FF 79 B8 11 AF 38 57 D6 71 8E 5F 0F 91", 16);
    BytesVector data = read_from_string("7C 3D 26 F7 73 77 63 5A 5E 43 E9 B5 CC 5D 05 92 6E 26 FF C5 22 0D C7 D4 05 F1 70 86 70 E6 E0 17", 32);
    BytesVector expected = read_from_string("0x41 0x6e 0x6f 0x74 0x68 0x65 0x72 0x20 0x73 0x65 0x63 0x72 0x65 0x74 0x21 0x20 0x20 0x41 0x6e 0x64 0x20 0x61 0x6e 0x6f 0x74 0x68 0x65 0x72 0x2e 0x20 0x20 0x20", 32);

    CBCMode mode(std::make_unique<Botan::AES_256>(), std::make_unique<NoopPaddng>());
    mode.start(key, iv);

    BytesVector result = mode.decrypt_data(data);

    BOOST_CHECK( expected == result);

}
