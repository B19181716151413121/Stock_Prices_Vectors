//  main.cpp
//  Isolated Stock Prices
//
//  Stock reading program
//  Created by Brian Cobo and Robert Medrano on 9/19/18.
//  Copyright © 2018 Brian Cobo. All rights reserved.
//
//	Algorithm
//	Open directory and search for every file in there
//		Put files in a vector of strings
//		Open every file in the vector
//	Read each line from each folder
//		Split each line by the comma and put into a struct containing stock info
//		Put struct into a vector containing info for all stocks
//	Count each stock name that shows up in all files
//		Output stocks to text file in specific directory
//
//  Sources Used
//  Time Keeping: https://www.pluralsight.com/blog/software-development/how-to-measure-execution-time-intervals-in-c--
//  Parsing: https://stackoverflow.com/questions/11719538/how-to-use-stringstream-to-separate-comma-separated-strings
//  Opening Files from Folder: https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <Windows.h>
#include "Nodes.h";
using namespace std;


struct Stock//Stores information about each stock. Contains name, date, open price,
			//high, low, closing price, volume.
{
	string name;
	string date;
	float open;
	float high;
	float low;
	float close;
	float volume;
};

///function declarations
Stock dataSplitter(string data);//Takes string and splits it by comma and stores info into Stock
void printStocks(vector <Stock> data);//Writes stock info into text file
vector <Stock> readingFromFolder(vector <string> fileNames);//Reads all files from vector of file names strings
vector <string> getFileNames(string folder);//Takes path and puts all files into a vector
bool searchVector(vector <string> data, string name); //Search vector to see if item exists 

int main()
{
	vector <Stock> data;//Processed Data after put in struct
	vector <string> fileNames; //Vector containing names of files in folder
	int x;//Used for keeping terminal from quitting, no impact on main code

	fileNames = getFileNames("C:\\Users\\Brian\\Desktop\\Input_Files");
	cout << "READING FROM FILES" << endl;
	data = readingFromFolder(fileNames);

	cout << "PRINTING STOCKS" << endl;
	printStocks(data);//Outputs stock information on text file

	cout << "CREATING LIST OF STOCK NAMES";
	//stockNames = findAllStockNames(data);//Creates a vector of all unique stock names

	cout << endl << "Program Finished" << endl;
	cout << "Data Size: " << data.size();
	cin >> x;
	return 0;
}

Stock dataSplitter(string data)//Takes data from line, and returns it as a struct
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

void printStocks(vector <Stock> data)
{
	ofstream ofile("Output.txt");

	for (int i = 0; i < data.size(); i++)
	{
		ofile << "Name:   " << data[i].name << endl;
		ofile << "Date:   " << data[i].date << endl;
		ofile << "Open:   " << data[i].open << endl;
		ofile << "High:   " << data[i].high << endl;
		ofile << "Low:    " << data[i].low << endl;
		ofile << "Close:  " << data[i].close << endl;
		ofile << "Volume: " << data[i].volume << endl;
		ofile << endl << endl;
	}
	ofile.close();
}

vector <Stock> readingFromFolder(vector <string> fileNames)
{
	vector <Stock> stocks;
	int maxStock = 0;
	int maxFile = 0;
	for (int i = 0; i < fileNames.size(); i++)
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
		cout << "File #" << i + 1 << " Contains " << stockCount << " Stocks." << endl;
		if (stockCount > maxStock)
		{
			maxStock = stockCount;
			maxFile = i;
		}

	}
	cout << "The file with the most stocks is: " << "C:\\Users\\Brian\\Desktop\\Input_Files\\" + fileNames[maxFile] << "with " << maxStock << " stocks";
	cout << endl << endl;
	string pathName = "C:\\Users\\Brian\\Desktop\\Input_Files\\" + fileNames[maxFile];

	return stocks;
}

vector<string> getFileNames(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}
