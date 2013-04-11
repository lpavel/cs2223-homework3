#include<cstdio>
#include<cstdlib>
#include<cstring>
#include"Huffman.h"

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

    encode("Homework6.txt","after.txt");

    decode("after.txt","Homework6_final.txt");



     return 0;
}

