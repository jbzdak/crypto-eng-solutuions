//
// Created by jb on 7/28/17.
//

#ifndef CRYPTO_BOOK_EXCERCISES_UTILS_H_H
#define CRYPTO_BOOK_EXCERCISES_UTILS_H_H

#include <vector>

#include <cstdint>
#include <iostream>
#include <string>

typedef std::vector<std::uint8_t> BytesVector;

std::ostream& operator<<(std::ostream& out, const BytesVector vec);

std::vector<std::string> tokenize_string_with_spaces(const std::string& str);

BytesVector read_from_string(const std::string& str, int64_t expected_size=-1);

BytesVector elementwise_xor(const BytesVector& v1, const BytesVector& v2);
void elementwise_xor(const BytesVector& v1, const BytesVector& v2, BytesVector& out);

std::string to_string(BytesVector bv);

#endif //CRYPTO_BOOK_EXCERCISES_UTILS_H_H
