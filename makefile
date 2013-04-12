all: huffman.exe

huffman.exe:
	g++ main.cpp huffman.cpp huffman_decoder.cpp huffman.h -o huffman.exe


clean:
	rm sandbox.txt

