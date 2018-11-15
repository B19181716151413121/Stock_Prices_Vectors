#pragma once
#ifndef LINKEDLISTS_H
#define LINKEDLISTS_H
//#include <string>
//#include <iostream>
using namespace std;

class LinkedList
{
private:
	struct ListNode
	{
		string name;
		string date;
		float open;
		float high;
		float low;
		float close;
		float volume;
		struct ListNode *next;  // To point to the next node
	};

	ListNode *head;

public:
		// Constructor
		LinkedList()
		{
			head = nullptr;
		}

		// Destructor
		~LinkedList();

		// Linked list operations
		void appendNode(string name, string date, float open, float high, float low, float close, float volume)
		{
			ListNode *newNode;  // To point to a new node
			ListNode *nodePtr;  // To move through the list

			// Allocate a new node and store info there.
			newNode = new ListNode;
			newNode->name = name;
			newNode->date = date;
			newNode->open = open;
			newNode->high = high;
			newNode->low = low;
			newNode->close = close;
			newNode->volume = volume;
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
			ListNode *nodePtr;  // To move through the list

   // Position nodePtr at the head of the list.
			nodePtr = head;

			// While nodePtr points to a node, traverse
			// the list.
			while (nodePtr)
			{
				// Display the value in this node.
				 
				 cout << nodePtr->name << endl;
				 cout << nodePtr->date << endl;
				 cout << nodePtr->open << endl;
				 cout << nodePtr->high << endl;
				 cout << nodePtr->low << endl;
				 cout << nodePtr->close << endl;
				 cout << nodePtr->volume << endl;

				// Move to the next node.
				nodePtr = nodePtr->next;
			}
		}
};

#endif 