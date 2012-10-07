#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

double GetRandom(double Min, double Max)
{
    return ((double(rand()) / double(RAND_MAX)) * (Max - Min)) + Min;    
}

float RandomFloat(float min, float max)
{
    // this  function assumes max > min, you may want 
    // more robust error checking for a non-debug build
    float random = ((float) rand()) / (float) RAND_MAX;

    // generate (in your case) a float between 0 and (4.5-.78)
    // then add .78, giving you a float between .78 and 4.5
    float range = max - min;  
    return (random*range) + min;
}

int main(int argc, char** argv) {
    
    int qnt = 0, t = 1, tamM = 100;
    float erro = 0;
    double v,p;
    string aux;
    stringstream num;
    ostringstream num2;
    ofstream myfile;
    
    cin>>qnt;
    num << qnt;
    
    aux = num.str();
    aux+= ".in";
    
    myfile.open(aux.c_str());
    
    aux = num.str();
    aux+="\n";
    myfile << aux;
    
    num.str("");
    num << tamM;
    aux = num.str();
    aux+= "\n";    
    myfile << aux;
    
    num.str("");
    num << erro;
    aux = num.str();
    myfile << aux;
    
    srand( time( NULL ) ); 
    
    for (int i=0; i<qnt; i+=t)
    {
        v = GetRandom(0,RAND_MAX);
        p = GetRandom(0,tamM);
        
        myfile << "\n";
        num.str("");
        num << v;
        aux = num.str();
        
        int virgula = GetRandom(0,aux.size());
        
        if ((virgula != aux.size()-1) && (virgula != 0))
                aux[virgula] = '.';
        
        myfile << aux;               
        
        aux = aux.erase();
        
        myfile << ", ";
        num2.str("");
        num2 << p;
        aux = num2.str();
                
        myfile << aux;
        
    }
    
    myfile.close();

    return 0;
}

