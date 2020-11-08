#include "BPTree.h"

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
        // work_node = work_node->GetChildPtr(i);
    }
    if(work_node->is_leaf)
    {
        work_node->InsertIntoNode(key,value);
        if(work_node->total_children==MIN_NUM*2)
        {
            work_node->SplitNode();
        }
        data_nums++;
    }
    return;
}
