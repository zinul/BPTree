#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
// #include "InternalNode.h"
// #include "LeafNode.h"
using index_t = unsigned int;
const int MIN_NUM = 3;
const int MAX_NUM = MIN_NUM * 2 - 1;
const int LESS_THAN_MIN = -1;

struct Value
{
    Value() : domain(std::string()){};
    Value(const std::string str) : domain(std::string(str)){};
    std::string domain;
};

class Node
{
protected:
    int total_children;
    int cur_node_num;
    std::shared_ptr<Node> pre_node;
    std::shared_ptr<Node> next_node;
    std::shared_ptr<Node> parent_node;
    std::vector<index_t> keys;

public:
    Node()=default;
    Node(int node_nums) : Node() { cur_node_num = node_nums; }
    bool is_leaf;
    virtual std::vector<index_t>& GetKeys() = 0;
    virtual std::shared_ptr<Node>& GetPreNode() = 0;
    virtual std::shared_ptr<Node>& GetNextNode() = 0;
    virtual std::shared_ptr<Node>& GetParNode() = 0;
    virtual int& GetNumOfChildren() = 0;
    // virtual std::vector<Value>& GetValue(){};
    // virtual std::vector<std::shared_ptr<Node>>& GetChildPtr(){};
    // virtual void InsertIntoNode(index_t key, Value value)=0;
    // virtual void InsertIntoNode(index_t key,
    //                             std::shared_ptr<Node> new_node)=0;
    virtual void SplitNode() = 0;

    // virtual Value Search(index_t key)=0;
    virtual int SearchPos(index_t key) = 0;

    // virtual int DeleteOneItem(index_t key)=0;
    // virtual int LendOneItem()=0;
    // virtual void MergeNode()=0;
    virtual void UpdateKey(index_t old_key) = 0;

    friend void PrintNode(std::shared_ptr<Node> node);
    friend class BPTree;
};
class LeafNode :virtual public Node
{
private:
    std::vector<Value> values;

public:
    LeafNode() : Node() { is_leaf = true; };
    LeafNode(const int i) : Node(i)
    {
        is_leaf = true;
    }
    std::vector<Value>& GetValue() { return values; };
    virtual std::vector<index_t>& GetKeys() { return keys; }
    virtual std::shared_ptr<Node>& GetPreNode() { return pre_node; }
    virtual std::shared_ptr<Node>& GetNextNode() { return next_node; }
    virtual std::shared_ptr<Node>& GetParNode() { return parent_node; }
    virtual int& GetNumOfChildren() override { return total_children; };
    // { return this->value; };

    void InsertIntoNode(index_t key, Value value);
    virtual void SplitNode() override;

    // virtual Value Search(index_t key) override;
    int SearchPos(index_t key, bool is_search);
    virtual int SearchPos(index_t key) override;

    // virtual int DeleteOneItem(index_t key) override;
    // virtual int LendOneItem() override;
    // virtual void MergeNode() override;
    virtual void UpdateKey(index_t old_key) override;

    friend class BPTree;

    ~LeafNode(){};
};
class InternalNode :virtual public Node
{
private:
    std::vector<std::shared_ptr<Node>> child_ptr;

public:
    InternalNode() : Node()
    {
        is_leaf = false;
    };
    InternalNode(int i) : Node(i) {is_leaf=false;}

    std::vector<std::shared_ptr<Node>>& GetChildPtr() { return child_ptr; };
    virtual std::vector<index_t>& GetKeys() { return keys; }
    virtual std::shared_ptr<Node>& GetPreNode() { return pre_node; }
    virtual std::shared_ptr<Node>& GetNextNode() { return next_node; }
    virtual std::shared_ptr<Node>& GetParNode() { return parent_node; }
    virtual int& GetNumOfChildren() { return total_children; }

    void InsertIntoNode(index_t key, std::shared_ptr<Node> new_node);
    virtual void SplitNode() override;
    // Value Search(index_t key) override;

    virtual int SearchPos(index_t key) override;

    // int DeleteOneItem(index_t key) override;
    // int LendOneItem() override;
    // void MergeNode() override;
    virtual void UpdateKey(index_t old_key) override;

    friend class BPTree;

    // ~InternalNode(){};
};

class BPTree
{
private:
public:
    int data_nums;
    int node_nums;
    std::shared_ptr<Node> root_node;
    BPTree() : data_nums(0), node_nums(0)
    {
        root_node =
            std::dynamic_pointer_cast<Node>(std::make_shared<LeafNode>(0));
        root_node->is_leaf = true;
    };
    void Insert(index_t key, Value value);
    void Insert(std::fstream& in, int n);
    int Delete(index_t key);
    int Search(index_t key);
    void const PrintTree();
    // ~BPTree();
};
void PrintNode(std::shared_ptr<Node> node);