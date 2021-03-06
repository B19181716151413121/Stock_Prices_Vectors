#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <Windows.h>
#include <map>
#include <iterator>
#include <direct.h>
#include <ctime>
#pragma warning(disable : 4996)

//#include "Nodes.h";
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
void printOpenStocks(vector <Stock> data, int numberOfFile);//Writes open stock info into text file
void printCloseStocks(vector <Stock> data, int numberOfFile);//Writes close stock info into text file
vector <Stock> readingFromFolder(vector <string> fileNames);//Reads all files from vector of file names strings
vector <string> getFileNames(string folder);//Takes path and puts all files into a vector
vector <Stock> Occurences(vector<Stock> data, vector<Stock> NewData, int NumberOfFiles); //Tracks for a specific number of occurences of a stock ticker
vector <Stock> Compare(vector<Stock> data, vector <string> names, vector<Stock> &NewData); //compares data with names of tickers that are in all files and then puts it in NewData Vector
template<typename K, typename V>
bool findByValue(vector<K> & vec, map<K, V> mapOfElemen, V value); //Finds all the values with specific occurences(V = 24 for number of files)




int main()
{
	//Print time and start clock
	time_t rawtime;
	time(&rawtime);
	cout << ctime(&rawtime);
	auto start = chrono::steady_clock::now();//Begin counting time

	vector <Stock> data;//Processed Data after put in struct
	vector <string> fileNames; //Vector containing names of files in folder
	vector<Stock> NewData; // new data- ignoring tickers not in all files

	fileNames = getFileNames("C:\\3304 Input Files\\");
	_mkdir("C:\\3304 Output Files");
	data = readingFromFolder(fileNames);
	int NumberOfFiles = fileNames.size();
	cout << "Number Of Files = " << NumberOfFiles << endl;
	
	NewData = Occurences(data, NewData, NumberOfFiles);
	//cout << NewData.size();
	printOpenStocks(NewData, NumberOfFiles);
	printCloseStocks(NewData, NumberOfFiles);
	time(&rawtime);
	cout << ctime(&rawtime);
	auto end = chrono::steady_clock::now();// Stop time
	auto diff = end - start;

	cout << "Time Elapsed: " << chrono::duration <double, milli>(diff).count() / 1000 << " sec" << endl;
	system("pause");
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

void printOpenStocks(vector <Stock> data, int numberOfFiles)
{
	ofstream ofile("C:\\3304 Output Files\\Open_Prices.txt");
	for (unsigned int i = 0; i < data.size(); i++)
	{
		ofile << data[i].name << ',';
	}
	for (unsigned int j = 0; j < numberOfFiles; j++)
	{
		ofile << data[j].date << ',';
		for (unsigned int k = 0; k < data.size(); k++)
		{
			if(data[k].date == data[j].date)
				ofile << data[k].open << ',';
		}
	}
	ofile.close();
}

void printCloseStocks(vector <Stock> data, int numberOfFiles)
{
	ofstream ofile("C:\\3304 Output Files\\Close_Prices.txt");
	for (unsigned int i = 0; i < data.size(); i++)
	{
		ofile << data[i].name << ',';
	}
	for (unsigned int j = 0; j < numberOfFiles; j++)
	{
		ofile << data[j].date << ',';
		for (unsigned int k = 0; k < data.size(); k++)
		{
			if (data[k].date == data[j].date)
				ofile << data[k].close << ',';
		}
	}
	ofile.close();
}

vector <Stock> readingFromFolder(vector <string> fileNames)
{
	vector <Stock> stocks;
	int maxStock = 0;
	int maxFile = 0;
	for (unsigned int i = 0; i < fileNames.size(); i++)
	{
		int j = 0;
		string str;
		string beginPath = "C:\\3304 Input Files\\";
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
		if (stockCount > maxStock)
		{
			maxStock = stockCount;
			maxFile = i;
		}

	}
	string pathName = "C:\\3304 Input Files\\" + fileNames[maxFile];

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

//=====================
template<typename K, typename V>
bool findByValue(vector<K> & vec, map<K, V> mapOfElemen, V value) //Finds all the values with specific occurences(V = 24 for number of files)
{
	bool bResult = false;
	auto it = mapOfElemen.begin();
	// Iterate through the map
	while (it != mapOfElemen.end())
	{
		// Check if value of this entry matches with given value
		if (it->second == value)
		{
			bResult = true;
			// Push the key into map
			vec.push_back(it->first);
		}
		// Go to next entry in map
		it++;
	}
	return bResult;
}

vector <Stock> Occurences(vector<Stock> data, vector<Stock> NewData, int NumberOfFiles) //mapping and counting everytime a stock ticker duplicate is found.
{
	map<string, int> wordsCount;
	//Look if it's already there.
	for (unsigned int i = 0; i < data.size(); i++) {
		if (wordsCount.find(data[i].name) == wordsCount.end()) { //first time in list.
			wordsCount[data[i].name] = 1;
		} // Initialize it to 1.
		else { // Then seen it before and add 1
			wordsCount[data[i].name]++;
		}
	}
	vector<string>tickers;  // <<<-- this vector has all tickers in all the files
	//int value = 2; // probaly should make this more "dynamic" in the future for more files or less
	bool result = findByValue(tickers, wordsCount, NumberOfFiles);

	for (unsigned int i = 0; i < tickers.size(); i++) {
		//cout<<tickers[i]<<endl;
	}



	if (result) //print all the stock tickers
	{
		//cout << "Keys with value " << NumberOfFiles << " are," << endl;
		for (auto elem : tickers)
		{

			//cout << elem << endl;
		}
	}
	else
	{
		cout << "No Key is found with the given value" << endl;
	}

	vector <Stock> sortedData = Compare(data, tickers, NewData);
	return sortedData;
}

vector <Stock> Compare(vector<Stock> data, vector<string> names, vector<Stock> &NewData)
{
	int k = 0;
	for (int i = 0; i < names.size(); i++) {
		for (int j = 0; j < data.size(); j++) {

			if (names[i] == data[j].name) {
				NewData.push_back(data[j]);/*
				cout << NewData[k].name << ",";				//
				cout << NewData[k].date << ",";				//
				cout << NewData[k].open << ",";				//
				cout << NewData[k].high << ",";				//comment this stuff if you dont want to see all data in console
				cout << NewData[k].low << ",";				//
				cout << NewData[k].close << ",";			//
				cout << NewData[k].volume << "\n";	*/		//
				k++;
			}

		}
	}
	return NewData;
}
