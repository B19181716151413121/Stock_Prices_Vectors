#pragma once
#ifndef FILELIST_H
#define FILELIST_H
//#include <string>
//#include <iostream>
using namespace std;

class FileList
{
private:
	struct FileNode
	{
		string fileName;
		struct FileNode *next;  // To point to the next node
	};

	FileNode *head;

public:
	// Constructor
	FileList()
	{
		head = nullptr;
	}

	// Destructor
	//~FileList();

	// Linked list operations
	void appendNode(string fileName)
	{
		FileNode *newNode;  // To point to a new node
		FileNode *nodePtr;  // To move through the list

		// Allocate a new node and store info there.
		newNode = new FileNode;
		newNode->fileName = fileName;
		
		newNode->next = nullptr;

		// If there are no nodes in the list
		// make newNode the first node.
		if (!head)
			head = newNode;
		else  // Otherwise, insert newNode at end.
		{
			// Initialize nodePtr to head of list.
			nodePtr = head;

			// Find the last node in the list.
			while (nodePtr->next)
				nodePtr = nodePtr->next;

			// Insert newNode as the last node.
			nodePtr->next = newNode;
		}
	}

	void displayList() const
	{
		FileNode *nodePtr;  // To move through the list

// Position nodePtr at the head of the list.
		nodePtr = head;

		// While nodePtr points to a node, traverse
		// the list.
		while (nodePtr)
		{
			// Display the value in this node.

			cout << nodePtr->fileName << endl;

			// Move to the next node.
			nodePtr = nodePtr->next;
		}
	}
};

#endif 