// Brian Cobo

#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include "StockList.h"
#include "FileList.h"

using namespace std;

FileList getFileNames(string folder);

int main()
{
	auto start = chrono::steady_clock::now();

	FileList fileNames = getFileNames("C:\\Users\\Brian\\Desktop\\Input_Files"); //Store File Names in a linked list
	
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << "Time Elapsed: " << chrono::duration <double, milli>(diff).count() << " sec" << endl;


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

