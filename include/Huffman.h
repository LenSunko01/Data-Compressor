#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H

#include "HuffmanTree.h"

class Huffman {
public:
    Huffman() = default;
    static std::map<char, std::string> encode(std::map<char, uint64_t>& frequency_table);
    static std::map<std::string, char> create_table_code_symbol(std::map<char,
                                                                std::string>& code_table_symbol_code);
    void add_to_frequency_table(const char byte);
    std::map<char, uint64_t> get_frequency_table();
private:
    std::map<char, uint64_t> frequency_table;
    static void encode_each_symbol(HuffmanNode* node,
                                         const std::string& code,
                                         std::map<char, std::string>& code_table);
    static std::map<char, std::string> create_code_table(HuffmanNode* node);
};


#endif //HUFFMAN_HUFFMAN_H
