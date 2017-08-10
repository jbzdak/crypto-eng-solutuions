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
        "53 9B 33 3B 39 70 6D 14 90 28 CF E1 D9 D4 A4 07"
)


print(len(message))

aes = AES.new(key, AES.MODE_ECB)

decrypted = aes.decrypt(message)

print(decrypted)

to_encrypt = message_to_bytes(
    "29 6C 93 FD F4 99 AA EB 41 94 BA BC 2E 63 56 1D"
)

aes = AES.new(key, AES.MODE_ECB)
print (aes.encrypt(to_encrypt))
