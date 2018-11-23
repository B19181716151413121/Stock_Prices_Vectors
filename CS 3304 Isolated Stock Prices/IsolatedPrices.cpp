/*
// Brian Cobo
// Robert Medrano
// Parsing: https://stackoverflow.com/questions/11719538/how-to-use-stringstream-to-separate-comma-separated-strings
//  Opening Files from Folder: https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c


#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include "StockList.h"
#include "FileList.h"

using namespace std;

FileList getFileNames(string folder);//Takes in string of path to folder, function gets all files inside of folder to read 


int main()
{
	cout << "Program Begin" << endl;
	auto start = chrono::steady_clock::now();//Begin counting time

	FileList fileNames = getFileNames("C:\\Users\\Brian\\Desktop\\Input_Files"); //Store File Names in a linked list
	StockList stocks = fileNames.iterateThroughFiles(fileNames);//Go through each file to store info
	
	//stocks.displayList();//Displays Stock info

	auto end = chrono::steady_clock::now();// Stop time
	auto diff = end - start;
	cout << "Program End" << endl;
	cout << "Time Elapsed: " << chrono::duration <double, milli>(diff).count()/1000 << " sec" << endl;


	system("pause");
	return 0;
}

FileList getFileNames(string folder)//Retrieves all file names in folder and stores it into a linked list
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
*/