//
// Created by jb on 7/29/17.
//
#include <utils.h>


int main(){
    BytesVector c1 = read_from_string("46 64 DC 06 97 BB FE 69 33 07 15 07 9B A6 C2 3D 2B 84 DE 4F 90 8D 7D 34 AA CE 96 8B 64 F3 DF 75", 32);
    BytesVector c2 = read_from_string("51 7E CC 05 C3 BD EA 3B 33 57 0E 1B D8 97 D5 30 7B D0 91 6B 8D 82 6B 35 B7 8B BB 8D 74 E2 C7 3B", 32);
    BytesVector p1 = read_from_string("43 72 79 70 74 6F 67 72 61 70 68 79 20 43 72 79 70 74 6F 67 72 61 70 68 79 20 43 72 79 70 74 6F", 32);

    BytesVector p1_xor_p2= elementwise_xor(c1, c2);
    BytesVector p2 = elementwise_xor(p1_xor_p2, p1);

    std::cout << to_string(p2) << std::endl;
}
