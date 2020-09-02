#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(std::map<char, uint64_t> &frequency_table) {
    std::priority_queue<HuffmanNode*,
            std::vector<HuffmanNode*>,
            HuffmanNode::compare_nodes> nodes_queue;
    create_nodes_queue(frequency_table, nodes_queue);
    build_tree(nodes_queue);
}

void HuffmanTree::create_nodes_queue(std::map<char, uint64_t> &frequency_table,
                        std::priority_queue<HuffmanNode*,
                        std::vector<HuffmanNode*>,
                        HuffmanNode::compare_nodes>& nodes_queue) {
    for (const auto &item : frequency_table) {
        auto *node = new HuffmanNode(item.first, item.second);
        nodes_queue.push(node);
    }
}

void HuffmanTree::build_tree(std::priority_queue<HuffmanNode*,
                             std::vector<HuffmanNode*>,
                             HuffmanNode::compare_nodes>& nodes_queue) {
    while (nodes_queue.size() != 1) {
        auto first_node = nodes_queue.top();
        nodes_queue.pop();
        auto second_node = nodes_queue.top();
        nodes_queue.pop();
        auto new_node = new HuffmanNode(first_node, second_node);
        nodes_queue.push(new_node);
    }
    root = nodes_queue.top();
}

HuffmanTree::~HuffmanTree() {
    delete root;
}

HuffmanNode* HuffmanTree::get_root() {
    return root;
}
