# HuffmanCodeGenerator
Accepts input strings and generates Huffman codes to compress the given string. 

A Huffman code uses a set of prefix code to compress the string with no loss of data (lossless).
David Huffman developed this algorithm in the paper “A Method for the Construction of
Minimum-Redundancy Codes” (http://compression.ru/download/articles/huff/
huffman_1952_minimum-redundancy-codes.pdf)

A program can generate Huffman codes from a string using the following steps:
· Generate a list of the frequency in which characters appear in the string using a map
· Inserting the characters and their frequencies into a priority queue (sorted first by the lowest
frequency and then lexicographically)
· Until there is one element left in the priority queue
· Remove two characters/frequencies pairs from the priority queue
· Turn them into leaf nodes on a binary tree
· Create an intermediate node to be their parent using the sum of the frequencies for those
children
· Put that intermediate node back in the priority queue
· The last pair in the priority queue is the root node of the tree
· Using this new tree, encode the characters in the string using a map with their prefix code by
traversing the tree to find where the character’s leaf is. When traversal goes left, add a 0 to
the code, when it goes right, add a 1 to the code
· With this encoding, replace the characters in the string with their new variable-length prefix
codes

In addition to the compress string, this program serializes the tree.
Tree serialization will organize the characters associated with the nodes using post order.


For decompression, two input arguments are be needed. The Huffman Code that was generated
by the compress method and the serialized tree string from the serializeTree method. 

Abstract Class Methods:

std::string compress(const std::string inputStr)
Compress the input string using the method explained above. Note: Typically we would be
returning a number of bits to represent the code, but for this project we are returning a string

std::string serializeTree() const
Serialize the tree using the above method. We do not need the frequency values to rebuild the
tree, just the characters on the leaves and where the branches are in the post order.

std::string decompress(const std::string inputCode, const std::string
serializedTree)
Given a string created with the compress method and a serialized version of the tree, return the
decompressed original string

