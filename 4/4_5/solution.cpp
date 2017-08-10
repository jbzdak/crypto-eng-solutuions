#include <algorithm>

#include "botan/aes.h"

#include <utils.h>
#include <modes.h>

int main(){
    BytesVector iv = read_from_string( "62 6C 6F 63 6B 20 63 69 70 68 65 72 73 20 20 20", 16);
    BytesVector message = read_from_string(
       "68 61 73 68 20 66 75 6E 63 74 69 6F 6E 73 20 78 62 6C 6F 63 6B 20 63 69 70 68 65 72 73 20 20 20",
       32
    );
    BytesVector key = read_from_string("80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01", 32);

    CBCMode cbcMode(std::make_unique<Botan::AES_256>(), std::make_unique<NoopPaddng>());

    cbcMode.start(key, iv);

    std::cout << cbcMode.encrypt_data(message) << std::endl;


}