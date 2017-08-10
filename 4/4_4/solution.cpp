#include <algorithm>

#include "botan/aes.h"

#include <utils.h>
#include <modes.h>

int main(){
    BytesVector iv = read_from_string( "62 6C 6F 63 6B 20 63 69 70 68 65 72 73 20 20 20", 16);
    BytesVector message = read_from_string(
            "7C 3D 26 F7 73 77 63 5A 5E 43 E9 B5 CC 5D 05 92 6E 26 FF C5 22 0D C7 D4 05 F1 70 86 70 E6 E0 17",
            32
    );
    BytesVector key = read_from_string("80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01", 32);

    CBCMode cbcMode(std::make_unique<Botan::AES_256>(), std::make_unique<NoopPaddng>());

    cbcMode.start(key, iv);

    std::cout << cbcMode.decrypt_data(message) << std::endl;
}