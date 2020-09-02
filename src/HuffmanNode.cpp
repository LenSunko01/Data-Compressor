#include "HuffmanNode.h"

HuffmanNode::HuffmanNode() {
    symbol = '0';
    frequency = 0;
    left_child = nullptr;
    right_child = nullptr;
}

HuffmanNode::HuffmanNode(char symbol_, uint64_t frequency_) : symbol(symbol_),
                                                              frequency(frequency_) {
    left_child = nullptr;
    right_child = nullptr;
}

HuffmanNode::HuffmanNode(HuffmanNode *left_child_,
                         HuffmanNode *right_child_) : left_child(left_child_),
                                                      right_child(right_child_) {
    symbol = '0';
    frequency = left_child->frequency + right_child->frequency;
}

HuffmanNode::~HuffmanNode() {
    delete left_child;
    delete right_child;
}

HuffmanNode* HuffmanNode::get_left_child() {
    return left_child;
}

HuffmanNode *HuffmanNode::get_right_child() {
    return right_child;
}

char HuffmanNode::get_symbol() {
    return symbol;
}


