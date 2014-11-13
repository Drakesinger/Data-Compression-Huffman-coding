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
	filename: 	C:\Development\Projects\NetworkProtocols\Huffman\Huffman\Utilties.h
	file path:	C:\Development\Projects\NetworkProtocols\Huffman\Huffman
	file base:	Utilties
	file ext:	h
	author:		Horia Mut

	purpose:
	*********************************************************************/
#pragma once

#include "Definitions.h"
/**
* Used to convert a Huffman code to it's integer equivalent.
* @param OutInt The integer representation of the Huffman code.
* @param Code The Huffman code to convert to an int.
* @param CodeLength The code's length.
*/
void ConvertHuffCodeToInt(int& OutInt, const HuffCode& Code, int CodeLength);

/**
* Used to read an uncompressed file.
* @param pFrequencies Pointer to an array where to store the frequencies of each symbol found.
* @param InputFile Name of the input file.
*/
int ReadUncompressedFile(int* pFrequencies, const char* InputFile);