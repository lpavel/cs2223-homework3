#include<string>
#include<cstring>
#include<vector>
#include<cstdio>
#include<map>
#include<set>
#include<algorithm>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include "Huffman.h"

using namespace std;

map<unsigned char,string> Table; // keeps the entire hash table that associate char to strings
//map<string,char> ReverseHash; // the reverse hash table for the decoder

bool comp_sort(Tnode a, Tnode b)
{
        return (a.freq < b.freq);
}

struct comp
{
    bool operator()(Tree* a, Tree* b)
    {
        return (a->sum < b->sum);
    }
};

void createMap(Tree* T, string str, ofstream& huffman_codes)
{
    if ( T->isEnd) // if it is end (has a character)
    {
        Table[T->ch] = str; // create the table

        if( T->ch != '\n' )  //particular case when \n is in the file
            huffman_codes<< T->ch << '\n' << str << '\n'; // solve the particular case
        else
            huffman_codes<< T->ch << str << '\n';  // create the reverseHash easy to read later
        return ;
    }

 //   cout<<str<<'\n';

    createMap( T->Tleft, str + "0", huffman_codes );
    createMap( T->Tright, str + "1", huffman_codes);
}



void encode(char* infileName, char* outfileName)
{
    multiset<Tree*,comp> huffmanT;
    multiset<Tree*,comp> :: iterator it1, it2;

    FILE *inFile;
    inFile = fopen(infileName,"r");
    ofstream huffman_codes("reverseHash.txt");
  //  FILE *outFile;
   // outFile = fopen(outfileName,"w");

    Tnode table[257];
    memset(&table,'\0',257*sizeof(Tnode));        //make the structs null
    int num_chars = createTable(inFile, table);     // the number of characters

    //sort(table, table+num_chars, comp_sort);

    //create the huffman tree

    for(int i=0; i<num_chars; i++)    //initialize the priority queue
    {
        Tree* T = new Tree;           // create a tree
        T->isEnd = true;
        T->ch = (unsigned char) table[i].ch;
        T->sum = table[i].freq;
        T->Tleft = NULL;
        T->Tright = NULL;
        huffmanT.insert(T);             // put it into the priority queue
        it1=huffmanT.begin();

    }

    while( huffmanT.size() != 1 )  // loops through the subtrees until it merges all of them
    {
        it1 = huffmanT.begin();  // take the first 2 smallest elements
        it2 = it1;
        it2++;

        Tree* p = new Tree;    // p puts together the 2 smallest ones
        p->isEnd = false;
        p->sum = (*it1)->sum + (*it2)->sum;
        p->Tleft = *it1;
        p->Tright = *it2;
        huffmanT.insert(p);    // insert the tree of trees into the big one
        huffmanT.erase(it1);   // erase the 2 trees that were put together
        huffmanT.erase(it2);
    }

    // The huffman Tree is created

    it1 = huffmanT.begin(); // extracts the Huffman tree
    createMap(*it1,"",huffman_codes);          // create the hash map using a pre-order traversal of the tree

    //The Hashmap is created

    // now just create the encoder

    fseek(inFile,0,SEEK_SET); // go through the file from the beginning

    createOutput(inFile,outfileName);

    // put the hashMap into a file to be used later

    fclose(inFile);
    huffman_codes.close();

}

void message0()
{
    printf("Error\n the syntax is:\n./ExecMyProgram Encode/Decode <input_file_path_to_compress> <path_of_output_file>\n");
}

void message1()
{
    printf("Only Encode or Decode can be the second parameter\n");
}

int createTable(FILE* infile, Tnode table[])
{
    int ascii[257];   // keeps the counting for the number of entries for each char
    unsigned char ch;
    memset(&ascii,'\0',257*sizeof(int));


    while(!feof(infile))    // read the entire input file
    {

        fscanf(infile,"%c",&ch);  // each char is counted
        ascii[(int) ch]++;
    }
    ascii[(int) ch]--;
    int counter = 0;

    for( int i=0; i<257; i++)  // puts the input data into the structure
        if( ascii[i] )
        {
            table[counter].ch = i;
            table[counter].freq = ascii[i];
            counter++;
        }

    return counter;

}

/*
void createOutput(FILE* infile, char* outfileName) // works without compressing the data even more
{
    char ch;
    ofstream outfile;
    outfile.open (outfileName);

   // while(!feof(infile))
    while(fscanf(infile,"%c",&ch)!=EOF)
    {
     //   fscanf(infile,"%c",&ch);
        outfile<<Table[ch];
    }

    outfile.close();
}*/


int binaryToBase10(char str[])
{
    int output = 0;

    for(int i=7; i >= 0; i--)
    {
        if( str[7-i] == '1')
            output += (1 << i);
    }

    return output;
}

void createOutput(FILE* infile, char* outfileName)
{
    unsigned char ch,ch2;           // the converted char
    ofstream outfile;
    outfile.open ("sandbox1.txt");  // open an auxiliary file

    while(fscanf(infile,"%c",&ch)!=EOF)
    {
        outfile<<Table[ch];   // create the bit string
    }

    outfile.close();


    FILE* inFromSandbox;
    inFromSandbox = fopen("sandbox1.txt","r");  // convert the sandbox to bits
    outfile.open(outfileName);   // open the compressed file
    char str[8];

    int counter=0;

    while( fscanf(inFromSandbox,"%c",&ch)!=EOF )    //read each 8 bits
    {
        if(counter == 8)
        {
            int binary = binaryToBase10(str);  // create the decimal
            ch2 = (unsigned char) binary;                 // convert the decimal to ascii
            outfile<< ch2;
            counter = 0;

        }

        str[counter++] = ch;
    }
    outfile.close();
    fclose(inFromSandbox);
}
