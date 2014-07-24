//
//  main.cpp
//  HuffmanEncoder
//
//  Created by Aamir Jawaid on 2014-07-22.
//  Copyright (c) 2014 Aamir Jawaid. All rights reserved.
//

#include <iostream>
#include "HuffmanTree.h"
#include "Helper.h"
using namespace std;
int main(int argc, const char * argv[])
{
    HuffmanTree* myTree = new HuffmanTree(&charList[0]);
    cout << "Enter the filePath: " ;
    string input, options, plainText, plainText2, plainText3;
    getline(cin, input);
    if (myTree->generateLeafFrequencyFromFile(input))
    {
        cout << "Huffman frequency was populated.\n";
    }
    else
    {
        cout << "Sorry, Huffman frequency was not populated. \n";
        goto cleanup;
    }
    myTree->generateTree();
    myTree->outputTree();
    
    
    plainText = "REMEMBER TO DRINK YOUR OVALTINE";
    plainText2 = "GIANTS BEAT DODGERS 10 TO 9 AND PLAY TOMORROW AT 1300";
    plainText3 = "SPACE THE FINAL FRONTIER THESE ARE THE VOYAGES OF THE BIT STREAM DAILY PROGRAMMER TO SEEK OUT NEW COMPRESSION";
    
    myTree->TestOutput(plainText);
    cout << "\n";
    myTree->TestOutput(plainText2);
    cout << "\n";
    myTree->TestOutput(plainText3);
cleanup:
    deletePtr(myTree);
    return 0;
}

