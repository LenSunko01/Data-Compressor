#ifndef HUFFMAN_BINARYFILEWRITER_H
#define HUFFMAN_BINARYFILEWRITER_H

#include <iostream>
#include <map>

class BinaryFileWriter {
public:
    BinaryFileWriter() = default;
    static void write_frequency_table(std::ostream &out,
                                      const std::map<char, uint64_t>& frequency_table);
    static void write_int32(std::ostream& out, int32_t data);
    static void write_byte(std::ostream& out, char byte);
};


#endif //HUFFMAN_BINARYFILEWRITER_H
