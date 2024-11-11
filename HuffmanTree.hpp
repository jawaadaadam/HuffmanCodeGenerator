#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <iostream>
#include <string>
#include <stack>
#include <map>

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"


class HuffmanTree{
public:

  std::string compress(const std::string inputStr);
  std::string serializeTree() const;
  std::string decompress(const std::string inputCode, const std::string serializedTree);

private:
    HuffmanNode * root;
    void preSearchTree(HuffmanNode * node, std::map<char, std::string>& h_codes, char key, std::string code) const;
    void postOrderHelper(HuffmanNode * node, std::string& serial) const;

};

#endif