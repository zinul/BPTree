#include "BPTree.h"
#include <iostream>
#include <fstream>
BPTree b_plus_tree;
int main(int argc,char *argv[])
{
    std::fstream fin("ip_log",std::fstream::in);
    b_plus_tree.Insert(fin,std::stoi(std::string(argv[1])));
    b_plus_tree.PrintTree();
    return 0;
}