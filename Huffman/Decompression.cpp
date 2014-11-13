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
	created:	12:11:2014   12:56
	filename: 	C:\Development\Projects\NetworkProtocols\Huffman\Huffman\Decompression.cpp
	file path:	C:\Development\Projects\NetworkProtocols\Huffman\Huffman
	file base:	Decompression
	file ext:	cpp
	author:		Horia Mut

	purpose:
	*********************************************************************/
#include "Decompression.h"
#include "Utilties.h"

/*
Header Format:
[Header Length]0
[Character]¶[Code length]¶[Code]0
*/

int ReadHeader(FILE* InFile, IntCodeMap& OutCodeMap)
{
	int HeaderLength = 0;
	int EncodingLength;
	int EncodedCharacter;

	if (InFile)
	{
		int CharacterRead;
		int CharacterSaved = 0;

		// Get HeaderLength (number of lines in the header).
		CharacterRead = fgetc(InFile);
		if (CharacterRead > 0)
		{
			HeaderLength = CharacterRead;
		}

		CharacterRead = fgetc(InFile);
		if (CharacterRead != LineDemiliter)
		{
			perror("Error continuing, did not find delimiter after HeaderLength.\nWrong Compression format?");
			return EXIT_FAILURE;
		}

		// Start reading the lines.
		// Format of a Line: [Character]|[Code length]|[Code]0
		int NumberOfLinesParsed = 0;
		int NumberOfSectionsParsed = 0;
		while (NumberOfLinesParsed < HeaderLength)
		{
			// Read the character.
			CharacterRead = fgetc(InFile);

			// Now we need to check regarding the format
			if (CharacterRead == LineDemiliter)
			{
				NumberOfLinesParsed++;
			}

			if (CharacterRead == SectionDelimiter)
			{
				NumberOfSectionsParsed++;
				if (NumberOfSectionsParsed == 1)
				{
					// Get the character's encoding length
					CharacterRead = fgetc(InFile);
					EncodingLength = CharacterRead;
				}
				else if (NumberOfSectionsParsed == 2)
				{
					// Get the character's encoding.
					CharacterRead = fgetwc(InFile);
					EncodedCharacter = CharacterRead;
					// Convert the Encoding to HuffmanCode.

					// Add character and it's encoding to the map.
					OutCodeMap[EncodedCharacter] = new HuffCharacter((char)CharacterSaved, EncodingLength);

					// Reset the number of sections read.
					NumberOfSectionsParsed = 0;
				}
			}

			if (NumberOfSectionsParsed == 0)
			{
				// Save the character.
				CharacterSaved = CharacterRead;
			}
		}
	}
	else
	{
		perror("Could not open the file to read.");
		return EXIT_FAILURE;
		fclose(InFile);
	}
	// Don't close as the calling function will use the File pointers.
	return 0;
}

void DecompressFile(const char* InputFile, const char* OutputFile)
{
	errno_t ErrorIn, ErrorOut;

	FILE* InFile;
	ErrorIn = fopen_s(&InFile, InputFile, "rb");
	FILE* OutFile;
	ErrorOut = fopen_s(&OutFile, OutputFile, "wb");

	IntCodeMap CodeMap;
	if (ReadHeader(InFile, CodeMap))
	{
		perror("Could not read header. Cannot decompress.");
		return;
	}

	if (InFile && OutFile)
	{
		int ReadBits = 0;
		int CharBuilder = 0;
		int ConstructedCharSize = 0;

		int ByteRead = 0;

		while (!feof(InFile))
		{
			ByteRead = fgetwc(InFile);

			// Now we need to read bit by bit, every time checking if the length of the encoding exists in our CodeMap.
			BitByBitReader(ByteRead, ReadBits, CharBuilder, CodeMap, OutFile);
		}

		// Write the last byte.
		fputc(ByteRead, OutFile);
	}
	else
	{
		perror("DecompressFile(). Could not open file to read/write.");
		printf("\nError code: \t InputFile %d\tOutputFile %d", ErrorIn, ErrorOut);
		return;
	}
}

void BitByBitReader(int& ByteRead, int& ReadBits, int& CharBuilder, IntCodeMap& CodeMap, FILE* OutFile)
{
	for (int iBit = 14/*7*/; iBit >= 0; iBit--)
	{
		CharBuilder ^= ((ByteRead >> iBit) & 1) << ReadBits;

		IntCodeMap::const_iterator iCodeMap = CodeMap.find(CharBuilder);
		if (iCodeMap != CodeMap.end())
		{
			// The encode exists!
			// Check the size.
			if (iCodeMap->second->Size != ReadBits)
			{
				// Wrong decode
			}
			else
			{
				printf("Found char %c\n", iCodeMap->second->Character);
				fputc(iCodeMap->second->Character, OutFile);
				CharBuilder = 0;
			}
		}
		ReadBits++;
		if (ReadBits == 14) ReadBits = 0;
		//ReadBits &= 7;
	}
}