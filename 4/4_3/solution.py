import codecs
import re

import numpy as np

def message_to_bytes(msg):
    msg = re.sub("\s", "", msg)
    msg = codecs.decode(msg.encode('ascii'), 'hex_codec')
    return msg

c1 = np.fromstring(
    message_to_bytes("46 64 DC 06 97 BB FE 69 33 07 15 07 9B A6 C2 3D 2B 84 DE 4F 90 8D 7D 34 AA CE 96 8B 64 F3 DF 75"),
    dtype=np.uint8
)

c2 = np.fromstring(
    message_to_bytes("51 7E CC 05 C3 BD EA 3B 33 57 0E 1B D8 97 D5 30 7B D0 91 6B 8D 82 6B 35 B7 8B BB 8D 74 E2 C7 3B"),
    dtype=np.uint8
)

p1 = np.fromstring(
    message_to_bytes("43 72 79 70 74 6F 67 72 61 70 68 79 20 43 72 79 70 74 6F 67 72 61 70 68 79 20 43 72 79 70 74 6F"),
    dtype=np.uint8
)

p1_xor_p2 = np.bitwise_xor(c1, c2)

print(p1_xor_p2.dtype)
print(p1.dtype)

p2 = np.bitwise_xor(p1, p1_xor_p2)

print(p2.tobytes().decode('ascii'))
