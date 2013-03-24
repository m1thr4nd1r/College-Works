/* 
 * File:   main.cpp
 * Author: M1thr4nd1r
 *
 * Created on 23 de Março de 2013, 21:48
 */

#include <cstdlib>
#include "Encode.h"

using namespace std;

int main(int argc, char** argv) {

    string input = "";
    
    input = "AAAAAABBBBBCCCCDDDEEF";
//    input = "AAAAAAAAAAAAAAABBBBBBBCCCCCCDDDDDDEEEEE";
//    input = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
//    input = "AAAAABBBCD";
//    input = "AABCCD";
//    input = "AABAAB";
    
//    cin>>input;
    
    encode(input);
    
    
    return 0;
}

