// Brian Cobo

#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include "StockList.h"
#include "FileList.h"

using namespace std;

FileList getFileNames(string folder);
StockList readingFromFolder(FileList fileNames);

int main()
{
	cout << "Program Begin" << endl;
	auto start = chrono::steady_clock::now();

	FileList fileNames = getFileNames("C:\\Users\\Brian\\Desktop\\Input_Files"); //Store File Names in a linked list
	StockList stocks = fileNames.iterateThroughFiles(fileNames);
	
	stocks.displayList();

	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << "Program End" << endl;
	cout << "Time Elapsed: " << chrono::duration <double, milli>(diff).count()/1000 << " sec" << endl;


	system("pause");
	return 0;
}

FileList getFileNames(string folder)
{
	FileList names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
			{
				names.appendNode(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

/*
StockList readingFromFolder(FileList fileNames)
{
	StockList stocks;
	StockList *nodeptr;
	StockList *head;

	nodeptr = head;

	while (nodeptr)
	{
		int j = 0;
		string str;
		string beginPath = "C:\\Users\\Brian\\Desktop\\Input_Files\\";
		string fileName = fileNames[i];
		string fullPath = beginPath + fileName;
		ifstream path(fullPath);
		int stockCount = 0;

		if (!path)
			cerr << "Could not open the file!" << endl;
		while (getline(path, str))
		{
			stocks.push_back(dataSplitter(str));
			stockCount++;
		}

		nodePtr = nodePtr->next;
	}
	return stocks;
}

tock dataSplitter(string data)//Takes data from line, and returns it as a struct
{
	Stock stockData;
	istringstream ss(data);
	string token;
	vector <string> rawData;//Vector to move info from streamed line to stuct

	while (getline(ss, token, ','))
	{
		rawData.push_back(token);
	}

	stockData.name = rawData[0];
	stockData.date = rawData[1];
	stockData.open = stof(rawData[2]);
	stockData.high = stof(rawData[3]);
	stockData.low = stof(rawData[4]);
	stockData.close = stof(rawData[5]);
	stockData.volume = stof(rawData[6]);

	return stockData;
}
*/