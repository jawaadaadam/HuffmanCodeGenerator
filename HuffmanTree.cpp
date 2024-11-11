#include "HuffmanTree.hpp"

//This function helps traverse the tree in preorder
void HuffmanTree::preSearchTree(HuffmanNode * node, std::map<char, std::string>& h_codes, char key, std::string code) const{

    if(node == nullptr) //base case
        return;

    if((node->isLeaf()) && (node->getCharacter() == key)) //if matches key then code saved
        h_codes[key] = code;

    preSearchTree(node->left, h_codes, key, code + "0");
    preSearchTree(node->right, h_codes, key, code + "1");

}

//This function helps to traverse the tree in post order
void HuffmanTree::postOrderHelper(HuffmanNode * node, std::string& serial) const{

    std::string conv_ch;

    if(node == nullptr){ //base case
        return;
    }

    postOrderHelper(node->left, serial);
    postOrderHelper(node->right, serial);

    if(node->isLeaf()){ // if the node is a leaf then we update the serialized tree string

        conv_ch = (node->getCharacter());
        serial += "L" + conv_ch;

    }
    if(node->isBranch()){ //if the node is a branch then we update the serialized tree string

        serial += "B";

    }

}

//This function is used to compress a string to its binary huffman equivalent
std::string HuffmanTree::compress(const std::string inputStr){

    std::map<char, int> freq_table; //used to store characters and frequencies

    for(int i = 0; i < inputStr.size(); i++){ //loop through input string

        if(freq_table.count(inputStr[i]) == 0)
            freq_table.insert({inputStr[i], 1}); //add character and frequency
        else
            freq_table[inputStr[i]] = freq_table[inputStr[i]] + 1; //increase frequency if already in table

    }

    HeapQueue<HuffmanNode*, HuffmanNode::Compare> p_queue; //priority queue to store character and frequency

    for (auto entry : freq_table){ //loop to populate priority queue

        HuffmanNode * node = new HuffmanNode(entry.first, entry.second);
        p_queue.insert(node);

    }


    do{ //generate huffman tree

        HuffmanNode * l1 = p_queue.min(); //take minimum entires and combine into subtree
        p_queue.removeMin();
        HuffmanNode * l2 = p_queue.min();
        p_queue.removeMin();

        HuffmanNode * b1 = new HuffmanNode('\0', (l1->getFrequency() + l2->getFrequency()), nullptr, l1, l2);

        l1->parent = b1;
        l2->parent = b1;

        p_queue.insert(b1); //push subtree to queue

    }while(p_queue.size() > 1);

    root = p_queue.min(); //min is now entire tree

    std::map<char, std::string> h_codes; //map to store huffman codes

    for( auto entry : freq_table){ //loop through tree to generate huffman code

        std::string code = "";
        preSearchTree(root, h_codes, entry.first, code); //use preorder traversal to generate huffman code

    }

    std::string compressed_string = "";

    for (auto i : inputStr) //loop through input string and convert characters to huffmancode equivalent
        compressed_string += h_codes[i];


    return compressed_string; //return compressed string

}

//This function is used to serialize the tree into a string
std::string HuffmanTree::serializeTree() const{

    std::string serial = ""; 
    postOrderHelper(root, serial); //use post order traversal to generate serialized string

    return serial; //return serialized string

}

//This function is used to decompress a string encoded using the huffman code
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){

    std::stack<HuffmanNode*> rebuild; //stack used to rebuild the tree

    for (auto ch : serializedTree){ //loop through the serialized tree

        if(ch == 'L'){ //if 'L' then we are at a leaf
            continue; //skip to next iteration 
        }

        else if(ch == 'B'){ //if 'B' then we are at a branch so combine leaves as children of branch

            HuffmanNode * right = rebuild.top(); //first leaf is at top of stack 
            rebuild.pop();
            HuffmanNode * left = rebuild.top(); //second leaf is next value in stack
            rebuild.pop();

            HuffmanNode * branch = new HuffmanNode('\0', 0, nullptr, left, right); //generate branch node
            rebuild.push(branch);

            right->parent = branch;
            left->parent = branch;

        }
        else if((ch != 'L') && (ch != 'B')){ //is a character as part of the original string 

            HuffmanNode * node = new HuffmanNode(ch, 0); //push to stack 
            rebuild.push(node);

        }
    
    }

    HuffmanNode * root = rebuild.top(); //the root is now stored at top of the stack 
    rebuild.pop();


    HuffmanNode * cursor = root; //used to traverse tree
    std::string decoded_string = "";
    std::string conv_ch;

    for (auto code : inputCode){ //loop through compressed string

        if(code == '0'){ //choose which direction to traverse tree
            cursor = cursor->left;
        }
        else{
            cursor = cursor->right;
        }
        if(cursor->isLeaf()){ //if is a leaf then it contains a character
            conv_ch = (cursor->getCharacter());
            decoded_string += conv_ch;
            cursor = root;

        }

    }

    return decoded_string; //return decompressed string

}

