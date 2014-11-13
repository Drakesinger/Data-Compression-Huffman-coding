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
	created:	12:11:2014   11:48
	filename: 	C:\Development\Projects\NetworkProtocols\Huffman\Huffman\Utilties.cpp
	file path:	C:\Development\Projects\NetworkProtocols\Huffman\Huffman
	file base:	Utilties
	file ext:	cpp
	author:		Horia Mut

	purpose:
	*********************************************************************/
#include "Utilties.h"
#include <math.h> // Used for Binary Format number to Integer conversion.
#include <bitset>

void ConvertHuffCodeToInt(int& OutInt, const HuffCode& Code, int CodeLength)
{
	int TempInt = 0;

	HuffCode::const_pointer iHuffCode = Code.data();

	for (size_t n = Code.size(); 0 < n; --n, iHuffCode++)
	{
		int TempVal;
		if (*iHuffCode == '0')
		{
			TempVal = 0;
		}
		else
		{
			TempVal = 1;
		}
		TempInt += TempVal * std::pow(2, n - 1);
	}
	OutInt = TempInt;
}

int ReadUncompressedFile(int* pFrequencies, const char* InputFile)
{
	// Get the text file.
	FILE* TextFile;
	fopen_s(&TextFile, InputFile, "r");
	if (TextFile != nullptr)
	{
		// File opened correctly, get frequencies of each character.
		int Character;
		while (!feof(TextFile))
		{
			// Get character.
			Character = fgetc(TextFile);
			if (Character == -1) break;
			// Increment frequency of character.
			++pFrequencies[Character];
		};
	}
	if (fclose(TextFile))
	{
		perror("Error closing.");
		return EXIT_FAILURE;
	}
	return 0;
}