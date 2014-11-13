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
	filename: 	C:\Development\Projects\NetworkProtocols\Huffman\Huffman\Compression.h
	file path:	C:\Development\Projects\NetworkProtocols\Huffman\Huffman
	file base:	Compression
	file ext:	h
	author:		Horia Mut

	purpose:
	*********************************************************************/
#pragma once

#include "Definitions.h"

/**
* Internal use only.
* Write the header of a compressed file.
*
* Header Format:
* [Header Length]0
* [Character]¶[Code length]¶[Code]0
*
* @param CodeMap The Huffman code map of each Symbol and it's corresponding code.
* @param OutFile Pointer to the file to write to.
*/
void WriteHeader(HuffCodeMap& CodeMap, FILE* OutFile);

/**
* Compress a file using a Huffman encoding map.
* Uses bit by bit writing to the file stream.
* @param CodeMap Huffman Code map to use.
* @param InputFile Name of the uncompressed file.
* @param OutputFile Name of the compressed file.
*/
void CompressFile(HuffCodeMap& CodeMap, const char* InputFile, const char* OutputFile);

/* Internal use only.
* Builds a byte to write to a file stream given a Huffman Encoding of a specific length.
*
* Algorithm:
*	1.	Take the Huffman Code.
*	2.	Shift right by the number of bits already done
*	3.	Mask the other 7 bits (AND 0x0000001)
*	4.	Shift back to the left by how much of a byte was filled.
*	5.	Repeat until byte is filled.
*
* @param ByteBuilder The built byte that will be written to the file stream.
* @param HuffmanCode The Huffman code expressed in integer format.
* @param ConstructedByteSize How much of the byte was already constructed.
* @param AssignedBits Number of bits already assigned in the byte.
*/
void BuildByte(const int& CodeLength, int& ByteBuilder, const int& HuffmanCode, int& ConstructedByteSize, int AssignedBits, FILE* OutFile);