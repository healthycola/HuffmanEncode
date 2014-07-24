//
//  HuffEncNode.cpp
//  HuffmanEncoder
//
//  Created by Aamir Jawaid on 2014-07-24.
//  Copyright (c) 2014 Aamir Jawaid. All rights reserved.
//

#include "HuffmanTree.h"

HuffmanTree::HuffEncNode::HuffEncNode(char val, int freq)
{
    ASCIIVal = val;
    frequency = freq;
    leftNode = nullptr;
    rightNode = nullptr;
}

HuffmanTree::HuffEncNode::HuffEncNode(int freq, HuffEncNode* rNode, HuffEncNode* lNode, char val)
{
    ASCIIVal = val;
    frequency = freq;
    leftNode = lNode;
    rightNode = rNode;
}

HuffmanTree::HuffEncNode::~HuffEncNode()
{
    deletePtr(leftNode);
    deletePtr(rightNode);
}

bool HuffmanTree::HuffEncNode::compare(HuffEncNode* a, HuffEncNode* b)
{
    return (a->frequency > b->frequency);
}

void HuffmanTree::HuffEncNode::generateCodes(string input, map<char, string>* outputMap)
{
    if (leftNode == NULL && rightNode == NULL)
    {
        //leaf node
        (*outputMap)[ASCIIVal] = input;
        return;
    }
    
    leftNode->generateCodes(input + '1', outputMap);
    rightNode->generateCodes(input + '0', outputMap);
}

char HuffmanTree::HuffEncNode::deCode(string input, int* characterLocation)
{
    if (leftNode == NULL && rightNode == NULL)
    {
        //leaf node
        return ASCIIVal;
    }
    
    if (input[*characterLocation] == '0')
    {
        //go into the right node
        (*characterLocation)++;
        return rightNode->deCode(input, characterLocation);
    }
    else
    {
        //go into the left node
        (*characterLocation)++;
        return leftNode->deCode(input, characterLocation);
    }
}