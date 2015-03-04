# README

Author: Horia Mut

## How to use
Start with cmd and write Huffman.exe.
It will automatically inform you of the correct usage.
<pre>
Huffman.exe [Function Number][Input File Path][Output File Path];
</pre>

## Choices made for the implementation of the Huffman Coding algorithm

### Programming Language: C++

Easy: This is the most powerful language that I work with and the one I know best.

Problems: No methods for writing to a stream bit by bit. No data type that's less that 1 byte.
This makes the compression and decompression a chore.
In order to really write a compressed file, each Symbol's encoding must be written bit by bit, but you can only write byte by byte.
Take a look in the Compression.cpp source file to see how this was worked around so that we can write the encoding for each Symbol.

### Data Structures
By default, the Huffman algorithm uses a Tree data structure in order to construct the code for every character found in a "text".

Using three types of classes, FrequencyNode, RootNode, LeafNode, makes it easy to construct the tree.

My implementation uses these data structures:

* 1 Integer **Table** of 256 elements : <br/>
  Will contain the frequencies of each unique Symbol found in our input, that is in the ASCII table.
* 4 Classes:
  * **FrequencyNode**	: <br/>Parent Class. Contains the Frequency
  * **RootNode** 	: <br/>Derived Class. Contains pointers to a left FrequencyNode and a right FrequencyNode (and the sum of frequencies).
  * **LeafNode**		: <br/>Derived Class. Contains the Symbol (character) for which an encoding must be found
  * **HuffCharacter**	: <br/>Contains a char and the size of it's encoding in an int. Used for decompression.
* 1 Priority **Queue** : <br/>Used to order the leaf node at first then construct the tree by creating a root from 2 leaves, the queue automatically orders the nodes according to their frequency.
* 1 Struct **NodeCmp** : <br/>Used to provide the Priority Queue with a means of deciding which Node is greater than another Node. The overloaded operator returns the coparison result such as the Queue is ordered decreasingly (makes it easier to create the Tree)
* 1 Vector : **vector<char> HuffCode** : <br/>Contains the Huffman code in a char array format. (Not the easiest way, bit set may have been better).
* 2 Maps
  * **map&lt;char, HuffCode&gt; HuffCodeMap**	: <br/>Map containing each of the unique symbols found and their Huffman encoding.
  * **map&lt;int, HuffCharacter*&gt; IntCodeMap** : <br/>Map containing each of the unique symbols found and their encoding in integer format. Used for 	decompression

##### Reason
The algortihm has been started directly with a tree. Tried to use another type of structure in order to fake building a tree however that was to no avail. Finally stayed with the Tree Structure in order to generate the Huffman Code for each Symbol.

## Compression Output

The header contains the following:

[Header Length = Number of Symbols]0<br/>
[Character]¶[Code length]¶[Code]0<br/>
[Character]¶[Code length]¶[Code]0<br/>
[Character]¶[Code length]¶[Code]0<br/>
[ENCODED FILE]<br/>

This will allow the program to decompress by reading the header, finding out how many unique symbols exist in the text, then for each symbol, it's encoded length, and it's encoding.

The line delimiters in the header is	: 	NUL / 0<br/>
The section delimiters in the header is: 	¶ 	/ 182

Compression rate:
The file tested "ARX_SOURCES_README.txt" contains			: 7518 Bytes<br/>
The output of the compression (including header) contains 	: 5241 Bytes<br/>
Rate (100- Compressed size / Uncompressed size * 100)		: 30.28 %<br/>

Comparison with Z-zip compression							: 3411 Bytes<br/>
Rate of Compression with Z-zip algorithm:					: 54.63 %<br/>

Possible reasons: Header is smaller, algortihm is different.

## Remaining Issues

Decompression doesn't work. The encoding of some characters is greater than 8 bits and the reading is done over 8 bits, problematic.
The code is there, it is logically sound but doesn't correctly decompress.
