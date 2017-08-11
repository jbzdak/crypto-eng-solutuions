import tempfile
import typing

import binascii
import numpy as np
import math
from Crypto.Hash import SHA512
from Crypto.Hash.hashalgo import HashAlgo

import pathlib

import dbm.gnu, os, sys, time

Hash = np.ndarray

HashInput = np.ndarray

RainbowTable = typing.Mapping[Hash, HashInput]


def make_sha_512(N: int):

  class Sha512N(object):
    digest_size = N
    block_size = 128

    def __init__(self, hash=None):
      if hash is None:
        hash = SHA512.new()
      self.__hash = hash

    def copy(self):
      return Sha512N(self.__hash.copy())

    def digest(self):
      return self.__hash.digest()[:N]

    def update(self, data):
      return self.__hash.update(data)

    def hexdigest(self):
      return binascii.hexlify(self.digest()).decode('ascii')

    @classmethod
    def new(self, data=None):
      sha = Sha512N()
      sha.update(data)
      return sha
  return Sha512N



def int_to_hash_and_data(SHA512N, ii: int):
  data = ii.to_bytes(SHA512N.digest_size+1, byteorder='big')
  digest = SHA512N.new(data).digest()
  return digest, data


def generate_table(N:int, result):
  table_size = int(max(256, math.pow(256, N/2)))

  SHA512N = make_sha_512(N)

  for ii in range(table_size):
    digest, data = int_to_hash_and_data(SHA512N, ii)
    result[digest] = data

  return result, table_size


def find_collisions(N: int, rainbow_table):

  start = time.monotonic()

  table, table_size = generate_table(N, rainbow_table)

  print("Table Created")

  idx = table_size
  SHA512N = make_sha_512(N)

  while idx:
    idx+=1
    digest, data = int_to_hash_and_data(SHA512N, idx)
    if digest in table:

      return [N, time.monotonic() - start] + [binascii.hexlify(x) for x in (digest, data, table[digest])]


def solution_dict():

  for N in range(1, 7):
    print(find_collisions(N, {}))


def solution_dbm():

  tmpdir = pathlib.Path(__file__).parent / 'tmpfiles'

  with open('dbm-log', 'w', buffering=1) as log:
    for N in range(1, 8):
      file_name = tmpdir / str(os.getpid())
      try:
        with dbm.gnu.open(str(file_name), 'nu') as db:
          print(find_collisions(N, db) + [file_name.stat()])
          print(find_collisions(N, db) + [file_name.stat()], file=log)
          print(file=log)
      finally:
        os.remove(str(file_name))

