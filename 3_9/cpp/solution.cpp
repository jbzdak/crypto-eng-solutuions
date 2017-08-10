#include "botan/aes.h"

#include <utils.h>

int main(){
    BytesVector key = read_from_string("80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01", 32);
    BytesVector message = read_from_string("29 6C 93 FD F4 99 AA EB 41 94 BA BC 2E 63 56 1D 16");
    std::cout << key << std::endl << message << std::endl;
    Botan::AES_256 cipher;
    cipher.set_key(key.data(), key.size());
    BytesVector response(16, 0);
    cipher.encrypt_n(message.data(), response.data(), 1);
    std::cout << response << std::endl;
}