README

Author: Horia Mut

 ===========================================================================
|	How to use:																|
 ===========================================================================
Start with cmd and write Huffman.exe.
It will automatically inform you of the correct usage.

Huffman.exe [Function Number][Input File Path][Output File Path];

 ===========================================================================
|	Choices made for the implementation of the Huffman Coding algorithm:	|
 ===========================================================================
 ================================
|	Programming Language: C++	 |
 ================================
 
 Easy: This is the most powerful language that I work with and the one I know best.
 Problems: No methods for writing to a stream bit by bit. No data type that's less that 1 byte.
 This makes the compression and decompression a chore. 
 In order to really write a compressed file, each Symbol's encoding must be written bit by bit, but you can only write byte by byte.
 Take a look in the Compression.cpp source file to see how this was worked around so that we can write the encoding for each Symbol.
 
 ================================
|	Data Structures				 |
 ================================
By default, the Huffman algorithm uses a Tree data structure in order to construct the code for every character found in a "text".
Using three types of classes, FrequencyNode, RootNode, LeafNode, makes it easy to construct the tree.

My implementation uses these data structures:
1 Integer Table of 256 elements : Will contain the frequencies of each unique Symbol found in our input, that is in the ASCII table.
4 Classes: 
	FrequencyNode	: Parent Class. Contains the Frequency
	RootNode	 	: Derived Class. Contains pointers to a left FrequencyNode and a right FrequencyNode (and the sum of frequencies).
	LeafNode		: Derived Class. Contains the Symbol (character) for which an encoding must be found
	HuffCharacter	: Contains a char and the size of it's encoding in an int. Used for decompression.
1 Priority Queue
	Used to order the leaf node at first then construct the tree by creating a root from 2 leaves, the queue automatically orders the nodes according to their frequency.
1 Struct NodeCmp
	Used to provide the Priority Queue with a means of deciding which Node is greater than another Node. The overloaded operator returns the coparison result such as the Queue is ordered decreasingly (makes it easier to create the Tree)
1 Vector
	vector<char> HuffCode : Contains the Huffman code in a char array format. (Not the easiest way, bit set may have been better).
2 Maps
	map<char, HuffCode> HuffCodeMap		: Map containing each of the unique symbols found and their Huffman encoding.
	map<int, HuffCharacter*> IntCodeMap : Map containing each of the unique symbols found and their encoding in integer format. Used for 	decompression

	Reasons:
The algortihm has been started directly with a tree. Tried to use another type of structure in order to fake building a tree however that was to no avail. Finally stayed with the Tree Structure in order to generate the Huffman Code for each Symbol.

 ================================
|	Compression Output			 |
 ================================
 
 The header contains the following:
 [Header Length = Number of Symbols]0
 [Character]¶[Code length]¶[Code]0
 [Character]¶[Code length]¶[Code]0
 [Character]¶[Code length]¶[Code]0
 [ENCODED FILE]
 
 This will allow the program to decompress by reading the header, finding out how many unique symbols exist in the text, then for each symbol, it's encoded length, and it's encoding.
 The line delimiters in the header is	: 	NUL / 0
 The section delimiters in the header is: 	¶ 	/ 182
 
 Compression rate:
 The file tested "ARX_SOURCES_README.txt" contains			: 7518 Bytes
 The output of the compression (including header) contains 	: 5241 Bytes
 Rate (100- Compressed size / Uncompressed size * 100)		: 30.28 %
 
 Comparison with Z-zip compression							: 3411 Bytes
 Rate of Compression with Z-zip algorithm:					: 54.63 %
 
 Possible reasons: Header is smaller, algortihm is different.
  
 ================================
|	Remaining Issues		 	 |
 ================================
 
 Decompression doesn't work. The encoding of some characters is greater than 8 bits and the reading is done over 8 bits, problematic.
 The code is there, it is logically sound but doesn't correctly decompress.
	