#include "../test/doctest.h"
#include "HuffmanTree.h"

TEST_CASE("1 testing the HuffmanTree constructor: more than one node") {
    std::map<char, uint64_t> frequency_table{{'a', 1}, {'b', 2}, {'c', 3}};
    HuffmanTree tree(frequency_table);
    HuffmanNode* root = tree.get_root();
    CHECK(root->get_symbol() == '0');
    HuffmanNode* left_child = root->get_left_child();
    CHECK(left_child->get_symbol() == 'c');
    HuffmanNode* right_child = root->get_right_child();
    CHECK(right_child->get_symbol() == '0');
    HuffmanNode* rl_child = right_child->get_right_child();
    CHECK(rl_child->get_symbol() == 'b');
    HuffmanNode* ll_child = right_child->get_left_child();
    CHECK(ll_child->get_symbol() == 'a');
}

TEST_CASE("1 testing the HuffmanTree constructor: one node") {
    std::map<char, uint64_t> frequency_table{{'a', 12}};
    HuffmanTree tree(frequency_table);
    HuffmanNode* root = tree.get_root();
    CHECK(root->get_symbol() == 'a');
}
