#include <bits/stdc++.h>
using namespace std;

class HuffmanNode {
public:
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    //HuffmanNode('a',100);'
};

class Compare {
public:
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->freq > right->freq;
    }
};

class HuffmanCoding {
private:
    HuffmanNode* root;
    unordered_map<char, string> huffmanCode;
    unordered_map<char, int> freqMap;

    void buildFrequencyMap(const string& data);
    void buildHuffmanTree();
    void generateCodes(HuffmanNode* node, const string& str);
    void writeEncodedData(const string& data, ofstream& outputFile);

public:
    HuffmanCoding() : root(nullptr) {}
    ~HuffmanCoding();
    void compress(const string& inputFileName, const string& outputFileName);
};

void HuffmanCoding::buildFrequencyMap(const string& data) {
    for (char ch : data) {
        freqMap[ch]++;
    }
}

void HuffmanCoding::buildHuffmanTree() {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    for (auto pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }


    while (minHeap.size() != 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        int sum = left->freq + right->freq;
        HuffmanNode* node = new HuffmanNode('\0', sum);
        node->left = left;
        node->right = right;

        minHeap.push(node);
    }

    root = minHeap.top();
}

void HuffmanCoding::generateCodes(HuffmanNode* node, const string& str) {
    if (!node) return;

    if (node->data != '\0') {
        huffmanCode[node->data] = str;
    }

    generateCodes(node->left, str + "0");
    generateCodes(node->right, str + "1");
}

void HuffmanCoding::writeEncodedData(const string& data, ofstream& outputFile) {
    string encodedString;
    for (char ch : data) {
        encodedString += huffmanCode[ch];
    }
    outputFile << encodedString;
}

HuffmanCoding::~HuffmanCoding() {
    // Implement a proper destructor to free the allocated memory
    function<void(HuffmanNode*)> deleteTree = [&](HuffmanNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    };
    deleteTree(root);
}

void HuffmanCoding::compress(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName, ios::in);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    string data((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    buildFrequencyMap(data);
    buildHuffmanTree();
    generateCodes(root, "");

    ofstream outputFile(outputFileName, ios::out);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    writeEncodedData(data, outputFile);
    outputFile.close();
}

int main() {
    HuffmanCoding huffman;
    string inputFileName = "input.txt";
    string outputFileName = "compressed.txt";

    huffman.compress(inputFileName, outputFileName);
    cout << "Compression complete." << endl;

    return 0;
}
