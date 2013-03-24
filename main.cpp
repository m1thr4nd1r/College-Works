/* 
 * File:   main.cpp
 * Author: M1thr4nd1r
 *
 * Created on 23 de Março de 2013, 21:48
 */

#include <iostream>
#include <fstream>
#include "Encode.h"
#include "Node.h"

using namespace std;

void remake_tree(string *encoded, Node** root)
{
    char bit = (*encoded)[0];
    
    (*encoded).erase((*encoded).begin());
    
    if (bit == '0')
    {
        Node * n = new Node();
    
        n->parent = *root;
        
        n->setBit('0');
        (*root)->child0 = n;
        remake_tree(encoded,&n);
                
        remake_tree(encoded,root);
    }    
    else if (((*root)->child0 != NULL) && ((*root)->child1 == NULL) && (bit == '1'))
    {
        Node *n = new Node();
        n->parent = *root;
        n->setBit('1');
        (*root)->child1 = n;
        remake_tree(encoded,&n);
        
        remake_tree(encoded,root);
    }
    else
        (*encoded).insert((*encoded).begin(),1,bit);
}

void finishTree(string *codes, Node* root)
{
    if (root->child0 != NULL)
        finishTree(codes,root->child0);
    if (root->child1 != NULL)
        finishTree(codes,root->child1);
    
    if ((root->child0 == NULL) && (root->child1 == NULL))
    {
        root->setSymbol((*codes)[0]);
        (*codes).erase((*codes).begin());
    }   
}

char extractCharacter(Node *root, string *msg)
{
    if ((root->child0 == NULL) && (root->child1 == NULL))
        return root->getSymbol();
    else
    {
        if ((*msg)[0] == '0')
        {
            (*msg).erase((*msg).begin());
            return extractCharacter(root->child0,msg);
        }
        else
        {
            (*msg).erase((*msg).begin());
            return extractCharacter(root->child1,msg);
        }
    }
}

string decode(Node *root, string msg)
{
    string decoded = "";
    while (!msg.empty())
        decoded+= extractCharacter(root,&msg);
    return decoded;
}

int main(int argc, char** argv) {

    string input = "", output = "", encoded = "";
    
    input = "AAAAAABBBBBCCCCDDDEEF";
//    input = "AAAAAAAAAAAAAAABBBBBBBCCCCCCDDDDDDEEEEE";
//    input = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
//    input = "AAAAABBBCD";
//    input = "AABCCD";
//    input = "AABAAB";
//    input = "AABABBCCCD";
//    input = "AB";
    
//    cin>>input;
    
    output = encode(input);
        
    fstream inFile;
    
    inFile.open("output.out",  fstream::binary | fstream::in | fstream::app);
    
    while(inFile.good())
    {
        char sheep = inFile.get();
        string bin = "";
        if ((int)sheep < 0)
        {
            short unsigned i = (short unsigned) sheep + 256;
            bin = intToBin(i);
            fill(&bin,8-bin.size());
            encoded+= bin;
        }
        else
        {
            bin = intToBin(sheep);
            fill(&bin,8-bin.size());
            encoded+= bin;
        }
    }
    
    inFile.close();
    
    encoded.erase(encoded.end()-8,encoded.end()); // Removendo o caracter do EOF
    
    string out = "";
    
    out = binToByte(encoded);
    
    out.assign(encoded,0,8);
    
    unsigned short qnt = binToInt(out);
    
    encoded.erase(encoded.begin(),encoded.begin() + 8); 
    
    Node *root = new Node();
    
    remake_tree(&encoded, &root);
    
    string chars = "";
    
    encoded.erase(encoded.begin());
    
    for (unsigned short i = 0; i < qnt; i++)
    {
        out.assign(encoded,0,8);
        encoded.erase(encoded.begin(),encoded.begin() + 8); 
        chars += binToInt(out);
    }
    
    finishTree(&chars,root);
    
    out.assign(encoded,encoded.size()-8,8);
    
    encoded.erase(encoded.size()-8,8);
    
    encoded += intToBin(binToInt(out));
    
    out = decode(root,encoded);
    
    cout << out;
    
    return 0;
}

