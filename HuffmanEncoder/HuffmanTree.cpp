//
//  HuffmanTree.cpp
//  HuffmanEncoder
//
//  Created by Aamir Jawaid on 2014-07-24.
//  Copyright (c) 2014 Aamir Jawaid. All rights reserved.
//

#include "HuffmanTree.h"
#include "Helper.h"

void HuffmanTree::generateTree()
{
    vector<HuffEncNode*> TreeNodes;
    for (map<char, int>::iterator it = frequencyChart.begin(); it != frequencyChart.end(); it++)
    {
        HuffEncNode* leafNode = new HuffEncNode((it)->first, (it)->second);
        TreeNodes.push_back(leafNode);
    }
    sort(TreeNodes.begin(), TreeNodes.end(), HuffEncNode::compare);
    while (TreeNodes.size() > 1)
    {
        //Pop last two elements
        HuffEncNode* RightNode = TreeNodes.back();
        TreeNodes.pop_back();
        HuffEncNode* LeftNode = TreeNodes.back();
        TreeNodes.pop_back();
        
        HuffEncNode* parentNode = new HuffEncNode(RightNode->frequency + LeftNode->frequency, LeftNode, RightNode);
        TreeNodes.push_back(parentNode);
        sort(TreeNodes.begin(), TreeNodes.end(), HuffEncNode::compare);
    }
    parentNode = TreeNodes.front();
    
    //Generate the encoding map
    parentNode->generateCodes("", &encodedMap);
}

void HuffmanTree::generateLeafFrequency(string input)
{
    //Reads a string and generates a frequncy list
    for (string::iterator it = input.begin(); it != input.end(); it++)
    {
        //ignore if it's not in our character list
        if (frequencyChart.count(*it) > 0)
            frequencyChart[*it]++;
    }
}

bool HuffmanTree::generateLeafFrequencyFromFile(string fileName)
{
    string line;
    ifstream myfile (fileName);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            transform(line.begin(), line.end(), line.begin(), ::toupper);
            generateLeafFrequency(line);
        }
        myfile.close();
        return true;
    }
    
    else cout << "Unable to open file" << "\n";
    return false;
}


void HuffmanTree::outputTree()
{
    for (map<char, string>::iterator it = encodedMap.begin(); it != encodedMap.end(); it++)
    {
        cout << it->first << " - " << it->second << "\n";
    }
}

string HuffmanTree::encode(string plainText)
{
    string output = "";
    for (string::iterator it = plainText.begin(); it != plainText.end(); it++)
    {
        if (encodedMap.count(*it) < 1)
            continue;   //ignore
        output += encodedMap[*it];
    }
    return output;
}

string HuffmanTree::decode(string encoded)
{
    string output = "";
    int characterLocation = 0;
    while (characterLocation < encoded.length())
    {
        output += parentNode->deCode(encoded, &characterLocation);
    }
    return output;
}

void HuffmanTree::TestOutput(string plainText)
{
    string encodedString, decodedString;
    encodedString = encode(plainText);
    decodedString = decode(encodedString);
    cout << "Read Message of " << plainText.size() << " Bytes.\n";
    cout << "Compressing " << plainText.size()*8 << " Bits into "<< encodedString.length() << " Bits. (" << (1.0 - (double)encodedString.length()/(double)plainText.size()/8.0) * 100.0 << "% compression)\n";
    cout << "Sending Message\n";
    cout << "Decompressing Message into " << decodedString.length() << " Bytes.\n";
    if (plainText == decodedString)
    {
        cout << "Message Matches!\n";
    }
}

HuffmanTree::HuffmanTree(const char* characterList)
{
    //Initialize characterList
    for (int i = 0; i < MAX_NUMBER_OF_CHARACTERS; i++)
    {
        frequencyChart[*characterList++] = 0;
    }
}

HuffmanTree::~HuffmanTree()
{
    frequencyChart.clear();
    encodedMap.clear();
    deletePtr(parentNode);
}