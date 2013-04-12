#include<cstdio>
#include<cstdlib>
#include<cstring>
#include"huffman.h"

using namespace std;
//works with no arguments
int main(){/*int argc, char* argv[])
{
   // open this when it certainly works

     if(argc != 4)
             message0();

     if( !strcmp(argv[1],"encode"))
             encode(argv[2],argv[3]);
     else if(!strcmp(argv[1],"decode"))
             decode(argv[2],argv[3]);
     else
             message1();
*/

    encode("index.html","bar.txt");

    decode("bar.txt","foo_final.txt");



     return 0;
}

