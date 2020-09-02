#ifndef HUFFMAN_HUFFMANARCHIVER_H
#define HUFFMAN_HUFFMANARCHIVER_H

#include <unordered_map>
#include <istream>
#include <ostream>

#include "Huffman.h"
#include "BinaryFileReader.h"
#include "BinaryFileWriter.h"

class HuffmanArchiver {
public:
    HuffmanArchiver() = default;
    void compress(std::istream& in, std::ostream& out);
    void extract(std::istream& in, std::ostream& out);
    void set_size_of_initial_data(std::size_t new_size);
    void set_table_symbol_code(std::map<char, std::string>& new_table);
    void set_encoded_data_string_size(int32_t new_size);
    void set_table_code_symbol(std::map<std::string, char>& new_table);
    std::size_t save(std::istream& in, std::ostream& out);
    void decode(std::istream& in, std::ostream& out);
    std::size_t get_size_of_initial_data() const;
    std::size_t get_size_of_processed_data() const;
    std::size_t get_size_of_ancillary_data() const;
private:
    const std::size_t number_of_bits_in_byte = 8;
    int32_t get_size_of_encoded_string();
    void count_size_of_ancillary_data();
    void read_frequency_table(std::istream& in);

    std::size_t size_of_initial_data_bytes = 0;
    std::size_t size_of_processed_data_bytes = 0;
    std::size_t size_of_ancillary_data_bytes = 0;
    int32_t encoded_data_string_size;
    std::map<char, uint64_t> frequency_table;
    std::map<char, std::string> code_table_symbol_code;
    std::map<std::string, char> code_table_code_symbol;
};


#endif //HUFFMAN_HUFFMANARCHIVER_H
