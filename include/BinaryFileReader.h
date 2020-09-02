#ifndef HUFFMAN_BINARYFILEREADER_H
#define HUFFMAN_BINARYFILEREADER_H

#include <iostream>
#include <map>
#include <memory>

class BinaryFileReader {
public:
    BinaryFileReader() = default;
    static char get_byte(std::istream& in);
    static std::size_t size_of_istream_bytes(std::istream& in);
    static std::map<char, uint64_t> read_frequency_table(std::istream &in);
    static int32_t read_int32(std::istream& in);
};


#endif //HUFFMAN_BINARYFILEREADER_H
