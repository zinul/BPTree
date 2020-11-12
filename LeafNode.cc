#include "BPTree.h"
extern BPTree b_plus_tree;
void LeafNode::InsertIntoNode(index_t key, Value new_value)
{
    // b_plus_tree.root_node;

    std::cout<<"LeafInsert"<<std::endl;
    std::cout<<total_children<<std::endl;

    if (total_children == 0)
    {
        keys.push_back(key);
        LeafNode::values.push_back(Value(new_value.domain));
        total_children++;
        std::cout<<total_children;
        return;
    }
    int insert_pos;
    for (insert_pos = 0; insert_pos < keys.size(); insert_pos++)
    {
        if (keys[insert_pos] > key)
        {
            keys.insert(keys.begin() + insert_pos, key);
            values.insert(values.begin() + insert_pos, new_value);
            total_children++;
            break;
        }
        else if (keys[insert_pos] == key)
        {
            values[insert_pos] = new_value;
            b_plus_tree.data_nums--;
            return;
        }
    }
    if (insert_pos == 0 && parent_node)
    {
        UpdateKey(keys[1]);
    }
}
void LeafNode::SplitNode()
{
    auto new_node = std::make_shared<LeafNode>(b_plus_tree.node_nums++);
    auto &new_keys = new_node->GetKeys();
    auto &new_value = new_node->GetValue();

    new_keys.insert(new_keys.begin(), keys.begin() + MIN_NUM, keys.end());
    keys.erase(keys.begin() + MIN_NUM, keys.end());
    new_value.insert(new_value.begin(), values.begin() + MIN_NUM, values.end());
    values.erase(values.begin() + MIN_NUM, values.end());

    total_children = MIN_NUM;
    new_node->total_children = MIN_NUM;

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
        new_parent_node->GetNumOfChildren()++;
        
        parent_node = new_parent_node;
        new_node->GetParNode()=new_parent_node;

        b_plus_tree.root_node =
            std::dynamic_pointer_cast<Node>(new_parent_node);
        std::cout<<new_parent_node->GetChildPtr()[0]<<std::endl;
    PrintNode(new_parent_node);
    }
    PrintNode(work_node);
    PrintNode(new_node);

    std::dynamic_pointer_cast<InternalNode>(parent_node)
        ->InsertIntoNode(new_keys[0], new_node);
    if (parent_node->GetNumOfChildren() == 2 * MIN_NUM)
    {
        parent_node->SplitNode();
    }
}
// Value Search(index_t key)
// {}
int LeafNode::SearchPos(index_t key)
{
    return SearchPos(key,true);
}
int LeafNode::SearchPos(index_t key, bool is_search)
{
    if (key > keys[total_children - 1])
    {
        if (is_search)
            return -1;
        else
            return total_children;
    }
    if (is_search)
    {
        for (int i = total_children - 1; i >= 0; i--)
        {
            if (keys[i] == key)
                return i;
            else if (keys[i] < key)
                break;
        }
        return -1;
    }
    else
    {
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
        return 0;
    }
}
// int DeleteOneItem(index_t key)
// {

// }
// int LendOneItem()
// {

// }
// void MergeNode()
// {

// }
void LeafNode::UpdateKey(index_t old_key)
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
