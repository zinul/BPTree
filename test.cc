#include "BPTree.h"
#include <iostream>
#include <fstream>
BPTree b_plus_tree;
int main(int argc,char *argv[])
{
    std::fstream fin("ip_log",std::fstream::in);
    b_plus_tree.Insert(fin,std::stoi(std::string(argv[1])));
    b_plus_tree.PrintTree();
    // std::shared_ptr<Node> node;
    // auto leaf_node=std::make_shared<LeafNode>();
    // leaf_node->GetValue().push_back(Value("dsa"));
    // node=std::dynamic_pointer_cast<Node>(leaf_node);
    // std::cout<<std::dynamic_pointer_cast<LeafNode>(node)->GetValue()[0].domain;
    return 0;
    
} 