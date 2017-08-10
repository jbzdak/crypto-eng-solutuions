We have following system:

     D(k1, plain) => e1; D(k2, e1) => e2

We'll try to crack it using birthday attack. Where k1 and k2 are two DES
round keys derived from ``k``.

We have some number of (`plain`, `e2`) pair.

Algorithm for retrieving key is as follows:

0. let ii = 0
1. We compute e1 for all `k1`.
2. For each k2 we decrypt `e2` to get `e1_candidate`. If we match any from the
   set computed in step `1` we check this with the rest of plaintext-ciphertext
   pairs and if they match we have both `k1` and `k1`.

Complexity is ``49bits`` + space for ``2^48`` of space for ``32+48`` bit slots.
I could find a way to trade off some space for computing power.
