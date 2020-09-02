#include <queue>
#include <iostream>
#include "Huffman.h"

std::map<char, std::string> Huffman::encode(std::map<char, uint64_t> &frequency_table) {
    std::map<char, std::string> code_table;
    if (!frequency_table.empty()) {
        HuffmanTree tree(frequency_table);
        code_table = create_code_table(tree.get_root());
    }
    return code_table;
}

std::map<char, std::string> Huffman::create_code_table(HuffmanNode* node) {
    std::map<char, std::string> code_table;
    encode_each_symbol(node, "", code_table);
    return code_table;
}

void Huffman::encode_each_symbol(HuffmanNode* node,
                                       const std::string& code,
                                       std::map<char, std::string>& code_table) {
    if (node == nullptr)
        return;
    HuffmanNode* left_child = node->get_left_child();
    HuffmanNode* right_child = node->get_right_child();
    if (!left_child && !right_child) {
        char symbol = node->get_symbol();
        if (code.empty()) {
            code_table[symbol] = "0";
        } else {
            code_table[symbol] = code;
        }
        return;
    }
    encode_each_symbol(left_child, code + "0", code_table);
    encode_each_symbol(right_child, code + "1", code_table);
}

void Huffman::add_to_frequency_table(const char byte) {
    ++frequency_table[byte];
}

std::map<std::string, char> Huffman::create_table_code_symbol(std::map<char,
                                                              std::string> &code_table_symbol_code) {
    std::map<std::string, char> code_table_code_symbol;
    for (const auto& item : code_table_symbol_code) {
        code_table_code_symbol[item.second] = item.first;
    }
    return code_table_code_symbol;
}

std::map<char, uint64_t> Huffman::get_frequency_table() {
    return frequency_table;
}

