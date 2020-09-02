#ifndef HUFFMAN_HUFFMANNODE_H
#define HUFFMAN_HUFFMANNODE_H
#include<cstdint>

class HuffmanNode {
public:
    HuffmanNode();
    HuffmanNode(char symbol_, uint64_t frequency_);
    HuffmanNode(HuffmanNode* left_child_,
                HuffmanNode* right_child_);
    ~HuffmanNode();
    HuffmanNode(const HuffmanNode& node) = delete;
    HuffmanNode* get_left_child();
    HuffmanNode* get_right_child();
    char get_symbol();
    struct compare_nodes {
        bool operator()(const HuffmanNode* l, const HuffmanNode* r) {
            return l->frequency > r->frequency;
        }
    };
    HuffmanNode& operator=(const HuffmanNode& node) = default;
private:
    char symbol;
    uint64_t frequency;
    HuffmanNode* left_child;
    HuffmanNode* right_child;
};


#endif //HUFFMAN_HUFFMANNODE_H
