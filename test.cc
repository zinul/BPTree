#include "BPTree.h"
#include <iostream>

int main()
{
    LeafNode ddd(0);
    std::shared_ptr<Node> root_node=std::dynamic_pointer_cast<Node>(std::make_shared<LeafNode>());
    auto temp=std::dynamic_pointer_cast<LeafNode>(root_node);
    temp->GetKeys().push_back(1);
    std::cout<<temp->GetKeys()[0];

    // ddd.GetKeys().push_back(2);
    root_node=std::dynamic_pointer_cast<Node>(temp);
    std::cout<<root_node->GetKeys()[0];
    // const int i=1;
    // auto b=std::make_shared<LeafNode>();
    // // std::shared_ptr<Node>a=std::dynamic_pointer_cast<Node>(b);
    // // auto &c=a->GetValue();
    // c.push_back(Value("a"));
    // std::cout<<c[0].domain<<std::endl;
    return 0;
}