//
// Created by jb on 7/28/17.
//

#include "utils.h"

#include <sstream>
#include <iostream>
#include <algorithm>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

typedef std::vector<std::uint8_t> BytesVector;

std::ostream& operator<<(std::ostream& out, const BytesVector vec)
{
    out << "BytesVector(";
    for (uint8_t elem: vec){
        out << std::hex << (int) elem << ", ";
    }
    out << ")";
    return out;
}

std::vector<std::string> tokenize_string_with_spaces(const std::string& str){
    std::vector<std::string> tokens;
    boost::split( tokens, str, boost::is_any_of(" \t") );
    return tokens;
}

BytesVector read_from_string(const std::string& str, int64_t expected_size){
    std::vector<uint8_t> response;
    for (std::string token: tokenize_string_with_spaces(str)){
        int64_t parsed;
        std::istringstream(token) >> std::hex >> parsed;
        assert(parsed >= std::numeric_limits<uint8_t>::min());
        assert(parsed <= std::numeric_limits<uint8_t>::max());
        uint8_t tmp = (uint8_t) parsed;
        response.push_back(tmp);
    }
    if (expected_size > -1){
        assert(response.size() == expected_size);
    }
    return response;
}

BytesVector elementwise_xor(const BytesVector& v1, const BytesVector& v2){
    assert(v1.size() == v2.size());
    BytesVector result;
    for (int ii=0; ii<v1.size(); ii++){
        result.push_back(v1[ii] ^ v2[ii]);
    }
    return result;
}

void elementwise_xor(const BytesVector& v1, const BytesVector& v2, BytesVector& out){
    assert(v1.size() == v2.size());
    assert(v1.size() == out.size());

    for (int ii=0; ii<v1.size(); ii++){
        out[ii] = (v1[ii] ^ v2[ii]);
    }
}

std::string to_string(BytesVector bv){
    std::string result;
    for (int ii=0; ii<bv.size(); ii++){
        result += (char) bv[ii];
    }
    return result;
}
