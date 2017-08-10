#include "utils.h"
#include "botan/sha2_64.h"
#include "botan/rng.h"
#include "sha512n.hxx"

#include <unordered_map>
#include <tuple>

#include <boost/functional/hash.hpp>

typedef std::array<uint8_t, 64> ShaHash;
typedef std::array<uint8_t, 64> HashedMessage;

template <typename T, int N>
struct Hash{
    size_t operator()(const std::array<T, N>&  arr){
        return boost::hash_range(arr.begin(), arr.end());
    }
};
template<size_t hash_size>
std::unique_ptr<std::unordered_map<std::array<uint8_t, hash_size>, HashedMessage>> prepare_rainbow_table(){
    size_t table_size = 1UL << hash_size;
    std::cout << "table size" << table_size << std::endl;
    std::unique_ptr<Botan::RandomNumberGenerator> rng = std::unique_ptr<Botan::RandomNumberGenerator>(
            Botan::RandomNumberGenerator::make_rng()
    );

    SHA512n<hash_size> hash;
    HashedMessage hashedMessage;
    std::array<uint8_t, hash_size> messageHash;
    auto result = std::make_unique<std::unordered_map<
            std::array<uint8_t, hash_size>, HashedMessage, Hash<uint8_t, hash_size>>();
    for (size_t idx=0; idx < table_size; idx++){

        rng->randomize(hashedMessage.data(), hashedMessage.size());
        hash.update(hashedMessage.data(), hashedMessage.size());
        hash.final(messageHash.data());

        result->operator[](messageHash) = hashedMessage;
    }

    return result;
};


int main(){
    std::cout << "8 Byte collision" << std::endl;

    auto rainbow8 = prepare_rainbow_table<8>();

    return 0;
}