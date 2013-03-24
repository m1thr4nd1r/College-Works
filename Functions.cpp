#include "Functions.h"

short binToInt(string n)
{
    unsigned short sum = 0;
    for (unsigned short i = n.size(); i > 0; i--)
        if (n[i-1] == '1')
            sum += pow(2,n.size()-i);
    return sum;
}

string intToBin(short n)
{
    string text = "";
    stringstream ss;
    
    if (n == 0 || n == 1) 
    {
        ss << n;
        text = ss.str();
    }
    else {
        text = intToBin(n >> 1);
        ss.str("");
        ss << (n & 0x1);
        text.append(ss.str());
    }
    
    return text;
}

void fill(string *text, short count)
{
    (*text).insert((*text).begin(),count,'0');
}