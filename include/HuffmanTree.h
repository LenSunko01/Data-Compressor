#ifndef HUFFMAN_HUFFMANTREE_H
#define HUFFMAN_HUFFMANTREE_H

#include <queue>
#include <map>
#include "HuffmanNode.h"

class HuffmanTree {
public:
    explicit HuffmanTree(std::map<char, uint64_t> &frequency_table);
    void create_nodes_queue(std::map<char, uint64_t> &frequency_table,
                            std::priority_queue<HuffmanNode*,
                            std::vector<HuffmanNode*>,
                            HuffmanNode::compare_nodes>& nodes_queue);
    void build_tree(std::priority_queue<HuffmanNode*,
                    std::vector<HuffmanNode*>,
                    HuffmanNode::compare_nodes>& nodes_queue);
    ~HuffmanTree();
    HuffmanNode* get_root();
private:
    HuffmanNode* root = nullptr;
};


#endif //HUFFMAN_HUFFMANTREE_H
