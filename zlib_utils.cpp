//
// Created by Shanuka Chathuranga on 6/23/25.
//

#include "zlib_utils.h"

#include <iostream>
#include <zlib.h>

namespace zlib_utils {
    std::vector<char> decompress_zlib(const std::vector<char> &compressedData) {

        std::vector<char> decompressedData;
        size_t bufferSize = 4096;
        decompressedData.resize(bufferSize);

        z_stream strm;
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;

        // Initialize the decompression stream
        // Z_OK indicates success.
        // 15 + 32: Auto-detect header type (gzip or zlib) and windowBits.
        //          15 is default windowBits for zlib. +32 is for auto-detection.
        if (inflateInit2(&strm, 15 + 32) != Z_OK) {
            std::cerr << "Zlib inflateInit2 failed.\n";
            return {}; // Return empty vector on error
        }

        // Set up input buffer
        strm.avail_in = compressedData.size();
        strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(compressedData.data()));

        int ret;
        // Loop to decompress data. Zlib might not decompress all in one go.
        do {
            // Set up output buffer
            strm.avail_out = decompressedData.size() - strm.total_out; // Remaining space in buffer
            strm.next_out = reinterpret_cast<Bytef*>(decompressedData.data() + strm.total_out);

            // Perform decompression
            ret = inflate(&strm, Z_NO_FLUSH); // Z_NO_FLUSH for incremental decompression

            // Handle possible errors from inflate
            if (ret == Z_STREAM_ERROR || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
                std::cerr << "Zlib inflate error: " << strm.msg << "\n";
                inflateEnd(&strm); // Clean up
                return {};
            }

            // If buffer is full and not done, resize it and continue
            if (strm.avail_out == 0 && ret != Z_STREAM_END) {
                // Double the buffer size or grow by a fixed amount
                size_t old_size = decompressedData.size();
                decompressedData.resize(old_size + bufferSize); // Grow by 'buffer_size'
                // Ensure the new part of the buffer is ready for output
            }

        } while (ret != Z_STREAM_END); // Loop until all data is decompressed

        // Clean up zlib stream
        inflateEnd(&strm);

        // Resize the vector to fit the actual decompressed data
        decompressedData.resize(strm.total_out);

        return decompressedData;



    }

}
