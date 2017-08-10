from Crypto.Cipher import AES
import codecs
import re

def message_to_bytes(msg):
    msg = re.sub("\s", "", msg)
    msg = codecs.decode(msg.encode('ascii'), 'hex_codec')
    return msg

key =  message_to_bytes(
    "80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
    "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01"
)

message = message_to_bytes(
    "87 F3 48 FF 79 B8 11 AF 38 57 D6 71 8E 5F 0F 91"
    "7C 3D 26 F7 73 77 63 5A 5E 43 E9 B5 CC 5D 05 92"
    "6E 26 FF C5 22 0D C7 D4 05 F1 70 86 70 E6 E0 17"
)

print(len(message))

aes = AES.new(key, AES.MODE_CBC, IV=message[:16])

decrypted = aes.decrypt(message[16:])

print(decrypted)
