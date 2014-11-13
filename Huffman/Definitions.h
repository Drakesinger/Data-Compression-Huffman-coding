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
	created:	12:11:2014   13:36
	filename: 	C:\Development\Projects\NetworkProtocols\Huffman\Huffman\Definitions.h
	file path:	C:\Development\Projects\NetworkProtocols\Huffman\Huffman
	file base:	Definitions
	file ext:	h
	author:		Horia Mut

	purpose:	Contains all the definitions useful for the program.
	*********************************************************************/
#pragma once

#include <queue>
#include <map>
#include <iterator>

//////////////////////////////////////////////////////////////////////////
// Compression / Decompression definitions

#define SectionDelimiter 182
#define LineDemiliter 0

#define InsertSectionDelimiter fputc(SectionDelimiter, OutFile)
#define InsertLineDemiliter fputc(LineDemiliter, OutFile)

//////////////////////////////////////////////////////////////////////////
// Main Program function definitions

#define READ_AND_SHOW_TREE	Function == 1
#define COMPRESS_FILE		Function == 2
#define DECOMPRESS_FILE		Function == 3

//////////////////////////////////////////////////////////////////////////
// Huffman types definitions

/*
Class used to store a Huffman code's corresponding Symbol and the code's length (since we are using integers to decompress and decode).
@param Character The Symbol corresponding to the Huffman code.
@param Size The size of the Huffman code.
*/
class HuffCharacter
{
public:
	char Character;
	int Size;
	inline HuffCharacter(char _Character, int _Size) : Character(_Character), Size(_Size) {}
};

/* Vector container for the route taken to reach a node.
Using char as type since this is expressed in binary format.
Used bool in the beginning but then we have problems when writing to a file.*/
typedef std::vector<char> HuffCode;

/* Map containing each of the unique symbols found in our input and it's corresponding route from the top of the Huffman tree. */
typedef std::map<char, HuffCode> HuffCodeMap;

/* Map containing each of the unique symbols found in our input and it's corresponding encoding in integer format. */
typedef std::map<int, HuffCharacter*> IntCodeMap;