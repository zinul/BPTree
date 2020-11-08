#include "BPTree.h"
#include <iostream>
int BPTree::data_nums=0;
int BPTree::node_nums=0;
int main()
{
    const int i=1;
    auto b=std::make_shared<LeafNode>();
    std::shared_ptr<Node>a=std::dynamic_pointer_cast<Node>(b);
    auto &c=a->GetValue();
    c.push_back(Value("a"));
    std::cout<<c[0].domain<<std::endl;
    return 0;
}