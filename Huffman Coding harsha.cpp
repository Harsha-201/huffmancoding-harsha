#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Huffman Tree Node structure
struct Node {
    char data;            // Character
    int freq;             // Frequency of the character
    Node* left;           // Pointer to the left child
    Node* right;          // Pointer to the right child

    // Constructor for leaf nodes
    Node(char data, int freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }

    // Constructor for internal nodes
    Node(Node* left, Node* right) {
        this->data = '\0';  // Internal nodes don't hold a character
        this->freq = left->freq + right->freq;
        this->left = left;
        this->right = right;
    }
};

// Comparison function for the priority queue (min-heap)
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Recursive function to print Huffman codes (preorder traversal)
void printHuffmanCodes(Node* root, string code) {
    if (!root) return;

    // If this is a leaf node, print the character and its code
    if (root->data != '\0') {
        cout << root->data << " : " << code << endl;
    }

    // Traverse left subtree with code "0"
    printHuffmanCodes(root->left, code + "0");

    // Traverse right subtree with code "1"
    printHuffmanCodes(root->right, code + "1");
}

// Function to build the Huffman Tree and print Huffman Codes in preorder traversal
void buildHuffmanTree(string S, vector<int> freq) {
    int n = S.size();
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Step 1: Create leaf nodes for each character and push them into the priority queue
    for (int i = 0; i < n; i++) {
        Node* newNode = new Node(S[i], freq[i]);
        minHeap.push(newNode);
    }

    // Step 2: Build the Huffman Tree by merging two minimum frequency nodes
    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with the sum of the two smallest frequencies
        Node* internalNode = new Node(left, right);

        // Push the new internal node back into the priority queue
        minHeap.push(internalNode);
    }

    // The root of the Huffman Tree is the only remaining node in the priority queue
    Node* root = minHeap.top();

    // Step 3: Print Huffman Codes in preorder traversal
    printHuffmanCodes(root, "");
}

int main() {
    // Example input
    string S = "abcdef";
    vector<int> freq = {5, 9, 12, 13, 16, 45};

    // Build the Huffman Tree and print Huffman Codes
    buildHuffmanTree(S, freq);

    return 0;
}
