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
	created:	12:11:2014   11:46
	filename: 	C:\Development\Projects\NetworkProtocols\Huffman\Huffman\Compression.cpp
	file path:	C:\Development\Projects\NetworkProtocols\Huffman\Huffman
	file base:	Compression
	file ext:	cpp
	author:		Horia Mut

	purpose:
	*********************************************************************/

#include "Compression.h"
#include "Utilties.h"

void WriteHeader(HuffCodeMap& CodeMap, FILE* OutFile)
{
	int HeaderLength;
	int Character;
	int EncodedCharacter;
	int EncodingLength;

	// Get the CodeMap size, this will be the Header Length.
	HeaderLength = CodeMap.size();
	// Write it to the file
	fputc(HeaderLength, OutFile);
	InsertLineDemiliter;

	// Navigate the map.
	for (HuffCodeMap::const_iterator iCodeMap = CodeMap.begin(); iCodeMap != CodeMap.end(); ++iCodeMap)
	{
		// Get the character and write it.
		Character = iCodeMap->first;
		fputc(Character, OutFile);
		InsertSectionDelimiter;

		// Get the character's code.
		HuffCode Code = iCodeMap->second;
		// Get it's length and write it.
		EncodingLength = Code.size();
		fputc(EncodingLength, OutFile);
		InsertSectionDelimiter;

		// Covert the Code to an int then call the ByteBuilder.
		ConvertHuffCodeToInt(EncodedCharacter, Code, EncodingLength);

		// Write it directly to the file
		fputwc(EncodedCharacter, OutFile);
		// But the best would be to build it by byte.

		// Finish the line.
		InsertLineDemiliter;
	}
}

void BuildByte(const int& CodeLength, int& ByteBuilder, const int& HuffmanCode, int& ConstructedByteSize, int AssignedBits, FILE* OutFile)
{
	// Start building the byte to write
	for (int i = 0; i < CodeLength; i++)
	{
		/*
		*	Algorithm:
		*	1.	Take the Huffman Code.
		*	2.	Shift right by the number of bits already done
		*	3.	Mask the other 7 bits(AND 0x0000001)
		*	4.	Shift back to the left by how much of a byte was filled.
		*	5.	Repeat until byte is filled.
		*/
		// Byte = Byte XOR ((Huffman Code >> Number of Bits already assigned) AND 0x00000001) << Bytes already made
		ByteBuilder ^= ((HuffmanCode >> AssignedBits) & 1) << ConstructedByteSize;

		// One more bit has been added.
		AssignedBits++;
		// If we have a full byte, write it.
		if (ConstructedByteSize == 7)
		{
			fputc(ByteBuilder, OutFile);
			// Reset the builder.
			ByteBuilder = 0;
		}
		// Set how much of a byte we have done.
		ConstructedByteSize++;
		// If 8 bits were done (76543210), reset it to 0.
		ConstructedByteSize &= 7;
	}
}

void CompressFile(HuffCodeMap& CodeMap, const char* InputFile, const char* OutputFile)
{
	// Open the old file and create a new file
	FILE* InFile; fopen_s(&InFile, InputFile, "r");
	FILE* OutFile;	fopen_s(&OutFile, OutputFile, "wb");

	if (InFile != nullptr && OutFile)
	{
		// Write header
		WriteHeader(CodeMap, OutFile);

		int HuffmanCode;
		int CodeLength;
		int AssignedBits = 0;
		int ByteBuilder = 0;
		int ConstructedByteSize = 0;

		int Character;
		while (!feof(InFile))
		{
			Character = fgetc(InFile);

			// Stop at end of file, this avoids Index Out_of_Bounds for the vector.
			if (Character == -1) break;

			// Get the Huffman code for the character.
			HuffCode CodeForChar = CodeMap.at((char)Character);
			// Get it's size.
			CodeLength = CodeForChar.size();

			// Convert the Huffman code to an int.
			ConvertHuffCodeToInt(HuffmanCode, CodeForChar, CodeLength);

			// Reset the number of assigned bits in the byte we want to write.
			AssignedBits = 0;

			// Build a byte to write.
			BuildByte(CodeLength, ByteBuilder, HuffmanCode, ConstructedByteSize, AssignedBits, OutFile);
		};

		// Write the last (non-full) character.
		fputc(ByteBuilder, OutFile);
	}
	else
	{
		perror("Could not open files for read and/or write.");

		fclose(InFile);
		fclose(OutFile);
		return;
	}

	// Cleanup.
	fclose(InFile);
	fclose(OutFile);
}