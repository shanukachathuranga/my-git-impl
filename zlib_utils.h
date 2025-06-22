//
// Created by Shanuka Chathuranga on 6/23/25.
//

#ifndef ZLIB_UTILS_H
#define ZLIB_UTILS_H
#include <vector>


namespace zlib_utils {
    std::vector<char> decompress_zlib(const std::vector<char>& compressedData);

};



#endif //ZLIB_UTILS_H
