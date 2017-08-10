import pytest
from Crypto.Hash import SHA512

import solution


@pytest.mark.parametrize(
  'N,data',
  [
      (ii, str(ii).encode('ascii'))
      for ii in range(64)
  ]
)
def test_sha_512_N(N: int, data):
  sha512 = SHA512.new(data)
  sha512N = solution.make_sha_512(N).new(data)
  normal_digest = sha512.digest()
  shorter_digest = sha512N.digest()
  assert len(shorter_digest) == N
  assert shorter_digest == normal_digest[:N]
  normal_hex = sha512.hexdigest()
  shorter_hex = sha512N.hexdigest()
  assert len(shorter_hex) == 2*N
  assert shorter_hex == normal_hex[:2*N]

