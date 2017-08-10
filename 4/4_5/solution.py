from Crypto.Cipher import AES
import codecs
import re
import os

def message_to_bytes(msg):
    msg = re.sub("\s", "", msg)
    msg = codecs.decode(msg.encode('ascii'), 'hex_codec')
    return msg

key =  message_to_bytes(
    "80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
    "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01"
)

message = message_to_bytes(
    "62 6C 6F 63 6B 20 63 69 70 68 65 72 73 20 20 20"
    "68 61 73 68 20 66 75 6E 63 74 69 6F 6E 73 20 78"
    "62 6C 6F 63 6B 20 63 69 70 68 65 72 73 20 20 20"
)

random_iv = os.urandom(16)

aes = AES.new(key, AES.MODE_CBC, IV=random_iv)

decrypted = aes.encrypt(message)

print(decrypted)
