#pragma once
#ifndef FILELIST_H
#define FILELIST_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//Linked list for storing all file names in folder
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

	//Read every file, extract data, and store it into stock linked list
	StockList iterateThroughFiles (FileList fileNames)
	{
		FileNode *nodePtr;
		StockList stocks;
		nodePtr = head;
		
		while (nodePtr)
		{
			
			string str;
			string beginPath = "C:\\Users\\Brian\\Desktop\\Input_Files\\";
			string fileName = nodePtr->fileName;
			string fullPath = beginPath + fileName;
			ifstream path(fullPath);
			vector <string> data;
			
			if (!path)
				cerr << "Could not open the file!" << endl;
			int i = 0;
			while (getline(path, str))//Seperates by comma
			{
				data = dataSplitter(str);
				stocks.appendNode(data[0], data[1], data[2], data[3], data[4], data[5], data[6]);
			}
			nodePtr = nodePtr->next;
		}
		
		return stocks;
	}
	
	vector <string> dataSplitter(string data)
	{
		StockList stock;
		istringstream ss(data);
		string token;
		vector <string> rawData;//Vector to move info from streamed line to stuct
		int i = 0;
		while (getline(ss, token, ','))
		{
			rawData.push_back(token);
		}
		return rawData;
	}

};

#endif 