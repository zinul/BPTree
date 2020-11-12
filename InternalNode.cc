#include "BPTree.h"
extern BPTree b_plus_tree;
// std::shared_ptr<Node> InternalNode::GetChildPtr(int i)
// {
//     return child_ptr[i];
// };
void InternalNode::SplitNode()
{
    auto new_node = std::make_shared<InternalNode>(b_plus_tree.node_nums++);
    auto &new_keys = new_node->GetKeys();
    auto &new_child_ptr = new_node->GetChildPtr();

    new_keys.insert(new_keys.begin(), keys.begin() + MIN_NUM, keys.end());
    keys.erase(keys.begin() + MIN_NUM, keys.end());
    new_child_ptr.insert(new_child_ptr.begin(), child_ptr.begin(),
                         child_ptr.end());
    child_ptr.erase(child_ptr.begin() + MIN_NUM, child_ptr.end());
    for (auto &child : new_child_ptr)
    {
        child->GetParNode() = new_node;
    }
    new_node->GetNumOfChildren() = MIN_NUM;
    total_children = MIN_NUM;

    std::shared_ptr<Node> work_node(this);
    if (next_node)
        next_node->GetPreNode() = std::dynamic_pointer_cast<Node>(new_node);
    new_node->pre_node = work_node;
    new_node->next_node = work_node->GetNextNode();
    work_node->GetNextNode() = new_node;

    if (work_node->GetParNode() == nullptr)
    {
        auto new_parent_node =
            std::make_shared<InternalNode>(b_plus_tree.node_nums++);
        auto &new_parent_child_ptrs = new_parent_node->GetChildPtr();
        auto &new_parent_keys = new_parent_node->GetKeys();
        new_parent_child_ptrs.push_back(work_node);
        new_parent_keys.push_back(keys[0]);

        parent_node = new_parent_node;
        b_plus_tree.root_node =
            std::dynamic_pointer_cast<Node>(new_parent_node);
    }
    std::dynamic_pointer_cast<InternalNode>(parent_node)
        ->InsertIntoNode(new_keys[0], new_node);
    if (parent_node->GetNumOfChildren() == 2 * MIN_NUM)
    {
        parent_node->SplitNode();
    }
    return;
}
void InternalNode::InsertIntoNode(index_t key,
                                  std::shared_ptr<Node> new_child_ptr)
{
    int insert_pos;
    for (insert_pos = 0; insert_pos < keys.size(); insert_pos++)
    {
        if (keys[insert_pos] > key)
        {
            keys.insert(keys.begin() + insert_pos, key);
            child_ptr.insert(child_ptr.begin() + insert_pos, new_child_ptr);
            total_children++;
            break;
        }
        else if (keys[insert_pos] == key)
        {
        }
    }
    if (insert_pos == 0 && parent_node)
    {
        UpdateKey(keys[1]);
    }
}
int InternalNode::SearchPos(index_t key)
{
    if (key >= keys[total_children - 1])
    {
        return total_children - 1;
    }

    for (auto i = total_children - 1; i >= 0; i--)
    {
        if (key < keys[i])
        {
            continue;
        }
        else
        {
            return i;
        }
    }
    return LESS_THAN_MIN;
}

void InternalNode::UpdateKey(index_t old_key)
{
    if (!parent_node)
    {
        return;
    }
    auto &keys = GetKeys();
    auto iter = std::find(keys.begin(), keys.end(), old_key);
    *iter = keys[0];
    if (iter == keys.begin())
    {
        parent_node->UpdateKey(old_key);
    }
}