#pragma once
#ifndef STOCKLIST_H
#define STOCKLIST_H
//#include <string>
//#include <iostream>
using namespace std;

//Linked list designed to store information for each stock
class StockList
{
private:
	struct StockNode
	{
		string name;
		string date;
		float open;
		float high;
		float low;
		float close;
		float volume;
		struct StockNode *next;  // To point to the next node
	};

	StockNode *head;

public:
		// Constructor
		StockList()
		{
			head = nullptr;
		}

		// Destructor
		//~StockList();

		// Linked list operations
		void appendNode(string name, string date, string open, string high, string low, string close, string volume)
		{
			StockNode *newNode;  // To point to a new node
			StockNode *nodePtr;  // To move through the list

			// Allocate a new node and store info there.
			newNode = new StockNode;
			newNode->name = name;
			newNode->date = date;
			newNode->open = stof(open);
			newNode->high = stof(high);
			newNode->low = stof(low);
			newNode->close = stof(close);
			newNode->volume = stof(volume);
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
			StockNode *nodePtr;  // To move through the list

   // Position nodePtr at the head of the list.
			nodePtr = head;

			// While nodePtr points to a node, traverse
			// the list.
			while (nodePtr)
			{
				// Display the value in this node.
				 
				 cout << "Name:   " << nodePtr->name << endl;
				 cout << "Date:   " << nodePtr->date << endl;
				 cout << "Open:   " << nodePtr->open << endl;
				 cout << "High:   " << nodePtr->high << endl;
				 cout << "Low:    " << nodePtr->low << endl;
				 cout << "Close:  " << nodePtr->close << endl;
				 cout << "Volume: " << nodePtr->volume << endl << endl;
				// Move to the next node.
				nodePtr = nodePtr->next;
			}
			cout << endl << endl;
		}
};

#endif 