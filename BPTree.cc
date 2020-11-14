#include "BPTree.h"

#include <unistd.h>

#include <fstream>
#include <iostream>

void BPTree::Insert(index_t key, Value value)
{
    auto work_node = root_node;
    while (!work_node->is_leaf)
    {
        int i = work_node->SearchPos(key);
        if (i == LESS_THAN_MIN)
        {
            i = 0;
        }
        work_node = std::dynamic_pointer_cast<InternalNode>(work_node)
                        ->GetChildPtr()[i];
        // std::cout << "i" << std::endl;
    }
    if (work_node->is_leaf)
    {
        std::dynamic_pointer_cast<LeafNode>(work_node)->InsertIntoNode(key,
                                                                       value);
        if (work_node->total_children == MIN_NUM * 2)
        {
            work_node->SplitNode();
        }
        PrintNode(work_node);
        data_nums++;
        std::cout <<"insert node:" <<node_nums <<std::endl;
    }
    return;
}
void BPTree::Insert(std::fstream& in, int n)
{
    while (!in.eof() && n > 0)
    {
        index_t key;
        Value value;
        in >> value.domain >> key;
        std::cout<<"insert key "<<key<< std::endl;
        Insert(key, value);
        std::cout<<"\n\n";
        PrintTree();
        n--;
    }
}
void const BPTree::PrintTree()
{
    auto work_node = root_node;
    std::cout << "BPTree:" << std::endl;
    while (!work_node->is_leaf)
    {
        auto first_node = work_node;
        // for (int i = 0; i < work_node->GetNumOfChildren(); i++)
        // {
        //     std::cout << work_node->GetKeys()[i] << std::endl;
        // }
        // std::cout << std::endl;
        while (work_node)
        {
            PrintNode(work_node);
            work_node = work_node->GetNextNode();
        }

        work_node = std::dynamic_pointer_cast<InternalNode>(first_node)
                        ->GetChildPtr()[0];
        // std::cout << std::dynamic_pointer_cast<InternalNode>(first_node)
        //                  ->GetChildPtr()[0]
        //           << std::endl;
    }

    while (work_node&&work_node->is_leaf)
    {
        work_node=std::dynamic_pointer_cast<LeafNode>(work_node);
        std::cout << "leaf node:"<<work_node->cur_node_num<< std::endl;
        for (int i = 0; i < std::dynamic_pointer_cast<LeafNode>(work_node)->GetNumOfChildren(); i++)
        {
            std::cout << std::dynamic_pointer_cast<LeafNode>(work_node)->GetKeys()[i]<<" " ;
            std::cout << std::dynamic_pointer_cast<LeafNode>(work_node)
                             ->GetValue()[i]
                             .domain
                      << std::endl;
            // sleep(1);
        }
        work_node = work_node->GetNextNode();
    }
}
void PrintNode(std::shared_ptr<Node> node)
{
    std::cout << "node:" << node->cur_node_num << std::endl;
    for (int i = 0; i < node->GetNumOfChildren(); i++)
    {
        std::cout << node->GetKeys()[i];
        if(node->is_leaf)
            std::cout << std::dynamic_pointer_cast<LeafNode>(node)->GetValue()[i].domain << std::endl;
        else
            std::cout<<std::endl;
    }
}