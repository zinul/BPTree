#include "BPTree.h"
// std::shared_ptr<Node> InternalNode::GetChildPtr(int i)
// {
//     return child_ptr[i];
// };
// int InternalNode::SearchPos(index_t key, bool is_search)
// {
//     if (key>=keys[total_children-1])
//     {
//         return total_children-1;    
//     }
    
//     for(auto i=total_children-1;i>=0;i--)
//     {
//         if(key<keys[i])
//         {
//             continue;
//         }
//         else
//         {
//             return i;
//         }
//     }
//     return LESS_THAN_MIN;
// }

void InternalNode::UpdateKey(index_t old_key)
{
    if (!parent_node)
    {
        return;
    }
    auto &keys = GetKeys();
    auto iter=std::find(keys.begin(), keys.end(), old_key);
    *iter=keys[0];
    if(iter==keys.begin())
    {
        parent_node->UpdateKey(old_key);
    }
}