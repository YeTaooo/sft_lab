#include <iostream>
#include <fstream>
#include <string.h>
#include <memory.h>
#define BUFFER_SIZE 1024

using namespace std;
int main (const int argc, const char* argv[])
{
    char * data;
    data = new char[BUFFER_SIZE];
    char ch;
    long length;
    int n, m, i, pos;
    ifstream file1;
    ofstream file2;
    file1.open(argv[1],ios::in);
    file2.open(argv[2],ios::out);
    if(!file1.good()|!file2.good())
    {
        //cout << "file not exist";
        return 0;
    }
    file1.seekg(0,ios::end);
    length = file1.tellg();
    n = length/BUFFER_SIZE ;
    if(length==0)
    {
        //cout << "empty File";
        return 0;
    }
       //cout << n;
       //cout << "\n";
    m = length%BUFFER_SIZE;
    //cout << m ;
    //cout << "\n";

    if(n==0){
       file1.seekg(0,ios::beg);
       file1.read(data,length);
        //cout << data;
       for(i=0; i< length/2; i++)
       {
           ch = data[i];
           data[i] = data[length-i-1];
           data[length-i-1] = ch;
       }
       file2.write(data,length);
    }
    else{
       pos = 1;
       
       do
       {
           file1.seekg(-(pos*BUFFER_SIZE), ios::end);
           file1.read(data,BUFFER_SIZE);
           //cout <<data ;
           for(i=0; i<BUFFER_SIZE /2; i++)
           {
               ch = data[i];
               data[i] = data[BUFFER_SIZE-i-1];
               data[BUFFER_SIZE-i-1] = ch;
           }
           file2.write(data,BUFFER_SIZE);
           
           n = n-1;
           pos = pos + 1;
           memset(data, 0, BUFFER_SIZE);
           
       }while(n>0);
       file1.seekg(0,ios::beg);
       length = m;
       file1.read(data,length);
       //cout << data;
       //cout << "\n";
       for(i=0; i< length/2; i++)
       {
           ch = data[i];
           data[i] = data[length-i-1];
           data[length-i-1] = ch;
       }
       file2.write(data,length);
       //cout << data;
    }
    delete data;
    file1.close();
    file2.close();
    return 0;

}
