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
	created:	06:11:2014   18:05
	filename: 	C:\Development\Projects\NetworkProtocols\Huffman\Huffman\Huffman.cpp
	file path:	C:\Development\Projects\NetworkProtocols\Huffman\Huffman
	file base:	Huffman
	file ext:	cpp
	author:		Horia Mut

	purpose:
	*********************************************************************/

#include "Huffman.h"
#include <iostream>

using std::cout;
using std::endl;
using std::copy;
using std::ostream_iterator;

FrequencyNode* BuildTree(const int* Frequencies, const int& UniqueSymbols)
{
	// Create the forest.
	std::priority_queue<FrequencyNode*, std::vector<FrequencyNode*>, NodeCmp> Forest;

	// For each Symbol, if it's frequency isn't null, create a LeafNode and push it to the bottom of the priority_queue.
	for (int iSymbol = 0; iSymbol < UniqueSymbols; ++iSymbol)
	{
		if (Frequencies[iSymbol] != 0)
		{
			Forest.push(new LeafNode(Frequencies[iSymbol], (char)iSymbol));
		}
	}

	// Now we construct the tree.
	while (Forest.size() > 1)
	{
		// Get the lowest frequency Node.
		FrequencyNode* ChildR = Forest.top();
		Forest.pop();

		// Get the next lowest frequency Node (can be equal to the last).
		FrequencyNode* ChildL = Forest.top();
		Forest.pop();

		// Create a root node containing both.
		FrequencyNode* Root = new RootNode(ChildR, ChildL);

		// Put it at the bottom of the queue. Then repeat.
		// This will construct the tree "recursively" in regard to the highest frequency found.
		Forest.push(Root);
	}

	// Tree is done. The top of the queue now contains the Huffman tree root node with all it's children.
	return Forest.top();
}

void GenerateCodes(const FrequencyNode* Node, const HuffCode& Code, HuffCodeMap& CodeMap)
{
	// If the node is a leaf node it contains a Frequency and a Symbol.
	if (const LeafNode* Leaf = dynamic_cast<const LeafNode*>(Node))
	{
		// Add the Symbol and it's corresponding Huffman code to the CodeMap.
		CodeMap[Leaf->Character] = Code;
	}
	// Otherwise it is a root node that only contains a frequency.
	// So we need to go deeper into the tree.
	else if (const RootNode* Root = dynamic_cast<const RootNode*>(Node))
	{
		// Left side is a 0.
		// Get the route up until now.
		HuffCode leftPrefix = Code;
		// Add a 0 to it.
		leftPrefix.push_back('0');
		// And start again until we get a leaf node.
		GenerateCodes(Root->LeftNode, leftPrefix, CodeMap);

		// If we got to a leaf, we have added the Symbol and it's route (code) to the map,
		// so now we check on the other side of the root because the leaf does not have any children.

		// Right side is a 1.
		// Get the root up to this node.
		HuffCode rightPrefix = Code;
		// Add a 1 to it.
		rightPrefix.push_back('1');
		// And look again deeper until we get a leaf node.
		GenerateCodes(Root->RightNode, rightPrefix, CodeMap);
	}
}

void PrintCodeMap(HuffCodeMap& CodeMap)
{
	// Show the codes.
	cout << endl << "Huffman Codes" << endl << "char | code" << endl;
	for (HuffCodeMap::const_iterator iCode = CodeMap.begin(); iCode != CodeMap.end(); ++iCode)
	{
		cout << iCode->first << "    | ";
		copy(iCode->second.begin(), iCode->second.end(), ostream_iterator<char>(cout));
		cout << endl;
	}
	cout << endl;
}