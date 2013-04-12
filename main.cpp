#include<cstdio>
#include<cstdlib>
#include<cstring>
#include"huffman.h"

using namespace std;
int main(int argc, char* argv[])
{

     if(argc != 4)
             message0();

     if( !strcmp(argv[1],"encode"))
             encode(argv[2],argv[3]);
     else if(!strcmp(argv[1],"decode"))
             decode(argv[2],argv[3]);
     else
             message1();


     return 0;
}

