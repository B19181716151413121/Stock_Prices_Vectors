#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <Windows.h>
#include <map>
#include <iterator>
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
void printStocks(vector <Stock> data);//Writes stock info into text file
vector <Stock> readingFromFolder(vector <string> fileNames);//Reads all files from vector of file names strings
vector <string> getFileNames(string folder);//Takes path and puts all files into a vector
bool searchVector(vector <string> data, string name); //Search vector to see if item exists 


void Occurences(vector<Stock> data, vector<Stock> NewData, int NumberOfFiles); //Tracks for a specific number of occurences of a stock ticker
void Compare(vector<Stock> data, vector <string> names, vector<Stock> &NewData); //compares data with names of tickers that are in all files and then puts it in NewData Vector
template<typename K, typename V>
bool findByValue(vector<K> & vec, map<K, V> mapOfElemen, V value); //Finds all the values with specific occurences(V = 24 for number of files)




int main()
{
	auto start = chrono::steady_clock::now();//Begin counting time

	vector <Stock> data;//Processed Data after put in struct
	vector <string> fileNames; //Vector containing names of files in folder
	int x;//Used for keeping terminal from quitting, no impact on main code
	vector<Stock> NewData; // new data- ignoring tickers not in all files



	fileNames = getFileNames("C:\\3304 Input Files\\");
	cout << "READING FROM FILES" << endl;
	data = readingFromFolder(fileNames);

	//cout << "PRINTING STOCKS" << endl;
	//printStocks(data);//Outputs stock information on text file

	//cout << "CREATING LIST OF STOCK NAMES";
	//stockNames = findAllStockNames(data);//Creates a vector of all unique stock names

	cout << "CREATING LIST OF STOCK NAMES WITH SPECIF NUMBER OF OCCUR\n";
	int NumberOfFiles = fileNames.size();
	Occurences(data, NewData, NumberOfFiles);
	//printStocks(NewData);
	auto end = chrono::steady_clock::now();// Stop time
	auto diff = end - start;
	cout << "Program End" << endl;
	cout << "Time Elapsed: " << chrono::duration <double, milli>(diff).count() / 1000 << " sec" << endl;
	///cout << "Data Size: " << data.size();
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

	for (unsigned int i = 0; i < data.size(); i++)
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
		cout << "File #" << i + 1 << " Contains " << stockCount << " Stocks." << endl;
		if (stockCount > maxStock)
		{
			maxStock = stockCount;
			maxFile = i;
		}

	}
	cout << "The file with the most stocks is: " << "C:\\3304 Input Files\\" + fileNames[maxFile] << "with " << maxStock << " stocks";
	cout << endl << endl;
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

void Occurences(vector<Stock> data, vector<Stock> NewData, int NumberOfFiles) //mapping and counting everytime a stock ticker duplicate is found.
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
		cout << "Keys with value " << NumberOfFiles << " are," << endl;
		for (auto elem : tickers)
		{

			//cout << elem << endl;
		}
	}
	else
	{
		cout << "No Key is found with the given value" << endl;
	}

	Compare(data, tickers, NewData);

}

void Compare(vector<Stock> data, vector<string> names, vector<Stock> &NewData)
{
	int k = 0;
	for (int i = 0; i < names.size(); i++) {
		for (int j = 0; j < data.size(); j++) {

			if (names[i] == data[j].name) {
				NewData.push_back(data[j]);
				/*cout << NewData[k].name << ",";				//
				cout << NewData[k].date << ",";				//
				cout << NewData[k].open << ",";				//
				cout << NewData[k].high << ",";				//comment this stuff if you dont want to see all data in console
				cout << NewData[k].low << ",";				//
				cout << NewData[k].close << ",";			//
				cout << NewData[k].volume << "\n";*/			//
				k++;
			}

		}
	}
}
