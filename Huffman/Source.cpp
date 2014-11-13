/*********************************************************************************
* Copyright (C) Haute-Ecole ARC - All Rights Reserved
*
* This file is part of <Networking Lab#1 Huffman Code Implementation>.
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Horia Mut <horia.mut@net2000.ch>, 06 November 2014
**********************************************************************************/
/********************************************************************
	created:	2014/11/12
	created:	06:11:2014   10:30
	filename: 	C:\Development\Projects\NetworkProtocols\Huffman\Huffman\Source.cpp
	file path:	C:\Development\Projects\NetworkProtocols\Huffman\Huffman
	file base:	Source
	file ext:	cpp
	author:		Horia Mut

	purpose:
	*********************************************************************/
#include <iostream>
#include "Definitions.h"

#include "Huffman.h"
#include "Utilties.h"
#include "Compression.h"
#include "Decompression.h"

const int UniqueSymbols = 256;

using std::cout;
using std::endl;
using std::copy;

int MainProgram(int& Function, const char* InputFile, const char* OutputFile);

int main(int argc, char* argv[])
{
	if (argc <= 2)
	{
		cout << "Wrong number of arguments provided." << endl;
		cout << "Correct usage:" << endl << "Huffman [Function nr][Input File][Output File]." << endl << "Functions: " << "\n\t" <<
			"1: Read Input File, generate Huffman Tree and print it." << "\n\t" <<
			"2: Read Input File, compress it under the name of Output File." << "\n\t" <<
			"3: Decompress Input file to Output File." << "\n\t" << endl;
	}
	else if (argc == 4)
	{
		int Function = atoi(argv[1]);
		const char* InputFile = argv[2];
		const char* OutputFile = argv[3];

		MainProgram(Function, InputFile, OutputFile);
	}

	return 0;
}

int MainProgram(int& Function, const char* InputFile, const char* OutputFile)
{
	// Build frequency table.
	int* pFrequencies = new int[UniqueSymbols]{0};

	if (ReadUncompressedFile(pFrequencies, InputFile))
	{
		perror("Failed to read Uncompressed file. Quiting.");
		return EXIT_FAILURE;
	};

	// Now construct the tree.
	FrequencyNode* Tree = BuildTree(pFrequencies, UniqueSymbols);

	// Generate the codes.
	HuffCodeMap CodeMap;
	GenerateCodes(Tree, HuffCode(), CodeMap);

	// Delete the tree since we don't need it anymore.
	delete Tree;
	Tree = nullptr;

	if (READ_AND_SHOW_TREE || COMPRESS_FILE)
	{
		// Show the codes.
		PrintCodeMap(CodeMap);
	}

	if (COMPRESS_FILE)
	{
		// Compress the file.
		cout << "Compressing file." << endl;
		CompressFile(CodeMap, InputFile, OutputFile);
	}

	if (DECOMPRESS_FILE)
	{
		cout << "Decompressing file." << endl;
		// Decompress the file.
		DecompressFile(InputFile, OutputFile);
	}

	return 0;
}