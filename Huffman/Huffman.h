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
	created:	06:11:2014   10:54
	filename: 	C:\Development\Projects\NetworkProtocols\Huffman\Huffman\Huffman.h
	file path:	C:\Development\Projects\NetworkProtocols\Huffman\Huffman
	file base:	Huffman
	file ext:	h
	author:		Horia Mut

	purpose:
	*********************************************************************/
#pragma once

#include "Definitions.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Classes for Huffman Tree Version

/* Tree node containing a frequency. */
class FrequencyNode
{
public:
	const int Frequency;
	virtual ~FrequencyNode() {}

protected:
	/*
	Default constructor.
	@param Frequency The Frequency of the symbol represented by the node or the sum of frequencies of the node's leaves.
	*/
	FrequencyNode(int Frequency) : Frequency(Frequency) {}
};

/* Tree root node containing two leaves. */
class RootNode : public FrequencyNode
{
public:
	FrequencyNode *const LeftNode;
	FrequencyNode *const RightNode;
	/* Constructs a root node containing a left and a right node, the frequency of the root node is the sum of the children's frequencies.
	@param LeftSide Left node
	@param RightSide Right node */
	inline RootNode(FrequencyNode* LeftSide, FrequencyNode* RightSide) : FrequencyNode(LeftSide->Frequency + RightSide->Frequency), LeftNode(LeftSide), RightNode(RightSide) {}
	/* Destroys the root node and it's children. Used when ordering. */
	~RootNode()
	{
		delete LeftNode;
		delete RightNode;
	}
};

/* A tree leaf containing a symbol and it's frequency. */
class LeafNode : public FrequencyNode
{
public:
	const char Character;
	/* Default constructor. Creates a LeafNode containing a symbol and it's corresponding frequency.
	@param Frequency Frequency at which the Symbol appears in the code.
	@param Character The Symbol to represent.*/
	LeafNode(int Frequency, char Character) : FrequencyNode(Frequency), Character(Character) {}
};

/*
Structure used in order to create a priority queue.
Normal priority queue functionality is to insert LeftHandSide before RightHandSide.
LeftHandSide is therefore smaller then RightHandSide.
In our case we do the opposite since we want to start at the end of the tree.
*/
struct NodeCmp
{
	/* The only in-structure operator that can be overridden and is a binary operator. */
	inline bool operator()(const FrequencyNode* LeftHandSide, const FrequencyNode* RightHandSide) const
	{
		return LeftHandSide->Frequency > RightHandSide->Frequency;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Function prototypes

/**
 * Constructs a Huffman Tree from a table of frequencies.
 * @param Frequencies Table containing the frequencies of each unique symbol.
 * @param UniqueSymbol Number of Unique symbols that the program can decode, also the length of the Frequencies table.
 */
FrequencyNode* BuildTree(const int* Frequencies, const int& UniqueSymbols);

/**
* Recursively generates the Huffman codes from the root node provided.
* Will check the left side first each time until it can find a leaf, then it will check for the right leaf and so on.
* Each time and for each leaf, the Prefix will change to contain the route taken to get to that leaf.
* @param Node The FrequencyNode to evaluate to a Leaf or Root. This node contains the full Huffman tree in the beginning.
* @param Code The route taken to reach the Node, corresponds to Huffman code of that particular Node.
* @param CodeMap out A mapping of each leaf Symbol and it's corresponding prefix (Huffman code).
*/
void GenerateCodes(const FrequencyNode* Node, const HuffCode& Code, HuffCodeMap& CodeMap);

/**
* Prints out the Huffman Code map.
* Format:
* character | encoding
* @param CodeMap The Huffman code map to print.
*/
void PrintCodeMap(HuffCodeMap& CodeMap);