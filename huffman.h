#ifndef HUFFMAN_H
#define HUFFMAN_H

typedef struct node
{
        int ch;  // character
        int freq;  // frequency
} Tnode;

typedef struct huffman_tree
{
    bool isEnd;   // knows if it has a char associated
    char ch;        // the char associated in case
    int sum;        // sum used for insertion in the huffman tree
    struct huffman_tree* Tleft;
    struct huffman_tree* Tright;
}Tree;

//static int compare(const void *element1, const void* element2);

void encode(char* infileName, char* outfileName);

void decode(char* infileName, char* outfileName);

void message0();

void message1();

void makeHash();

void createOutput(FILE* infile, char* outfileName);

int createTable(FILE* infile, Tnode table[]);

#endif

