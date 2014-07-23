//
//  main.cpp
//  HuffmanEncoder
//
//  Created by Aamir Jawaid on 2014-07-22.
//  Copyright (c) 2014 Aamir Jawaid. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

static const int MAX_NUMBER_OF_CHARACTERS = 37;    //A-Z,0-9 and a space
static const char charList[MAX_NUMBER_OF_CHARACTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3' ,'4', '5', '6', '7', '8', '9', '0', ' '};
template <class T>
void deletePtr(T* ptr)
{
    delete ptr;
}

//Hufman Encode
class HuffEncNode
{
private:
    HuffEncNode* leftNode;
    HuffEncNode* rightNode;
public:
    char ASCIIVal;
    int frequency;
    HuffEncNode(char val, int freq)
    {
        ASCIIVal = val;
        frequency = freq;
        leftNode = nullptr;
        rightNode = nullptr;
    }
    
    HuffEncNode(int freq, HuffEncNode* rNode, HuffEncNode* lNode, char val = '\0')
    {
        ASCIIVal = val;
        frequency = freq;
        leftNode = lNode;
        rightNode = rNode;
    }
    
    ~HuffEncNode()
    {
        deletePtr(leftNode);
        deletePtr(rightNode);
    }
    
    static bool compare(HuffEncNode* a, HuffEncNode* b)
    {
        return (a->frequency > b->frequency);
    }
};

class HuffmanTree
{
private:
    HuffEncNode* parentNode;
public:
    map<char, int, less<int>> frequencyChart;
    void generateTree()
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
    }
    
    void generateLeafFrequency(string input, const char* characterList)
    {
        //Initialize characterList
        for (int i = 0; i < MAX_NUMBER_OF_CHARACTERS; i++)
        {
            frequencyChart[*characterList++] = 0;
        }
        
        //Reads a string and generates a frequncy list
        for (string::iterator it = input.begin(); it != input.end(); it++)
        {
            frequencyChart[*it]++;
        }
    }
    
    void outputTree()
    {
        
    }
    ~HuffmanTree()
    {
        frequencyChart.clear();
        deletePtr(parentNode);
    }
};


int main(int argc, const char * argv[])
{

    // insert code here...
    HuffmanTree* myTree = new HuffmanTree();
    myTree->generateLeafFrequency("HELLO MY NAME IS AAMIR I AM 100", &charList[0]);
    myTree->generateTree();
    deletePtr(myTree);
    std::cout << "Hello, World!\n";
    return 0;
}

