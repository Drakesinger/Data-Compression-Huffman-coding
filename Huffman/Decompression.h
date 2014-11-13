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
	created:	12:11:2014   11:55
	filename: 	C:\Development\Projects\NetworkProtocols\Huffman\Huffman\Decompression.h
	file path:	C:\Development\Projects\NetworkProtocols\Huffman\Huffman
	file base:	Decompression
	file ext:	h
	author:		Horia Mut

	purpose:
	*********************************************************************/

#pragma once
#include "Huffman.h"

/**
* Reads the header of a compressed file. Internal use only.
* @param InFile Compressed file pointer to read.
* @param OutCodeMap Huffman Code Map output.
*/
int ReadHeader(FILE* InFile, IntCodeMap& OutCodeMap);

/**
* Decompress a file that was compressed with a Huffman encoding map.
* Uses bit by bit reading of the file stream.
* @param InputFile Name of the compressed file.
* @param OutputFile Name of the decompressed file.
*/

void DecompressFile(const char* InputFile, const char* OutputFile);

/**
* Read a file stream bit by bit and compare with a code map to see if the bits are not an encoded character.
* Inverse algorithm attempt of @see BuildByte.
* @param ByteRead The read byte.
* @param ReadBits Number of bits that have been already read.
* @param CharBuilder Symbol that needs to be decoded using the CodeMap.
* @param CodeMap Huffman code Map containing the code in integer format, it's size, and it's corresponding decoded Symbol.
* @param OutFile File stream to write the decoded Symbol.
*/
void BitByBitReader(int& ByteRead, int& ReadBits, int& CharBuilder, IntCodeMap& CodeMap, FILE* OutFile);