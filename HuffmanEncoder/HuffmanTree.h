//
//  HuffmanTree.h
//  HuffmanEncoder
//
//  Created by Aamir Jawaid on 2014-07-24.
//  Copyright (c) 2014 Aamir Jawaid. All rights reserved.
//

#ifndef __HuffmanEncoder__HuffmanTree__
#define __HuffmanEncoder__HuffmanTree__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include "Helper.h"

static const int MAX_NUMBER_OF_CHARACTERS = 37;    //A-Z,0-9 and a space
static const char charList[MAX_NUMBER_OF_CHARACTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3' ,'4', '5', '6', '7', '8', '9', '0', ' '};

using namespace std;
class HuffmanTree
{
private:
    class HuffEncNode
    {
    private:
        HuffEncNode* leftNode;
        HuffEncNode* rightNode;
    public:
        char ASCIIVal;
        int frequency;
        HuffEncNode(char val, int freq);
        HuffEncNode(int freq, HuffEncNode* rNode, HuffEncNode* lNode, char val = '\0');
        ~HuffEncNode();
        void generateCodes(string input, map<char, string>* outputMap);
        char deCode(string input, int* characterLocation);
        static bool compare(HuffEncNode* a, HuffEncNode* b);
    };
    HuffEncNode* parentNode;
public:
    map<char, int, less<int>> frequencyChart;
    map<char, string> encodedMap;
    void generateTree();
    void generateLeafFrequency(string input);
    bool generateLeafFrequencyFromFile(string fileName);
    void outputTree();
    string encode(string plainText);
    string decode(string encoded);
    void TestOutput(string plainText);
    HuffmanTree(const char* characterList);
    ~HuffmanTree();
};

#endif /* defined(__HuffmanEncoder__HuffmanTree__) */
