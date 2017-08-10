#include "utils.h"
#include "botan/sha2_64.h"
int main(){
    Botan::SHA_512 sha512;
    BytesVector vector = read_from_string("48 65 6C 6C 6F 2C 20 77 6F 72 6C 64 2E 20 20 20");
    sha512.update(vector.data(), vector.size());
    BytesVector response(sha512.output_length(), 0);
    sha512.final(response.data());

    std::cout << response;
}