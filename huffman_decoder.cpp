#include<string>
#include<sstream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<map>
#include<set>
#include<algorithm>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include "huffman.h"

using namespace std;

map<string,unsigned char> ReverseHash;  // the hash that map strings to chars


void decimalToBinary(int number, char str[])
{
    char str2[8];
    int counter = 0;
    do
    {
        if( ( number & 1) == 0 )
            str2[counter++]='0';
        else
            str2[counter++]='1';

        number >>= 1;
    }
    while(number);
    for( ; counter < 8 ; counter++)
        str2[counter] = '0';

    for(int i=0; i < 8; i++)
        str[i] = str2[7-i];
}

void createString(FILE* inFile, ofstream &outFile)
{
    unsigned char ch; // the char that stores the ascii
    int c;
    //while( (c = getchar(inFile))!=EOF )
    do
    {
        c = getc(inFile);
        //fscanf(inFile,"%hhu",&ch);
        ch = (unsigned char) c;

        int ascii = (int) ch; // ascii has the number of the character
        char str[8]; // stores the string of 8 bits

        str[0]='\0';

        decimalToBinary(ascii, str);

        for(int i=0; i < 8; i++)
            outFile << str[i];
    }
    while(c!=EOF);
}

void decode(char* infileName, char* outfileName)
{
/*
    ifstream inFile;
    inFile.open(infileName);
*/
    FILE* inFile;
    inFile = fopen(infileName,"r");
    ofstream outFile;
    outFile.open("sandbox.txt");  // first put the data into sandbox with string of 1's and 0's

    createString(inFile,outFile);
    fclose(inFile);
    outFile.close();

    makeHash();  // create ReverseHash

    char ch;
    string chstr; // converts the char to a string before concatenating
    string str = ""; // adds to the string till it finds it in the hash
    str.empty(); // empty it first

    ifstream inFile2;
    inFile2.open("sandbox.txt");
    outFile.open(outfileName);

    while(!inFile2.eof())
    {
        inFile2 >> ch;     //read one character
        str = str + ch;  // add the char to the string

        if(ReverseHash[str])  // if the string maps to something
        {
            outFile<<ReverseHash[str]; //print the char
            str.erase(0,str.size());   //empty the string to find the new map
        }
    }

   // cout<<str.size();

    inFile2.close();
    outFile.close();

}

void makeHash()
{

    FILE* inputHash;
    inputHash = fopen("reverseHash.txt","r");  //open reverseHash
    char str[100]; // used as buffer for reading
    unsigned char ch;  // the char to which will be maped

    bool isfirst = true;  // helps reading reverseHash

    char c[2];
    while(!feof(inputHash))
    {
        if( fgets(str, 100, inputHash) == NULL) // read and break at the end
            break;

        if( strcmp(str,"\n") )       // if only \n not need to make it null
            str[strlen(str)-1]='\0';  // otherwise get rid of the \n at the end

        if (isfirst)
        {
            strcpy(c,str); // create the char
            ch = c[0];
       //     cout<< ch<<'\n';
            isfirst = false;

        }
        else
        {
            string foo (str);  // create the string
            isfirst = true;

            ReverseHash[foo] = ch;
     //       cout<< foo<< " - "<<ReverseHash[foo]<<" \n";
        }
    }

}


