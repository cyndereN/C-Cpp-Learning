#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <ctime>
#include <vector>
#include <mutex>

#ifndef INCLUDE_STD_FILESYSTEM_EXPERIMENTAL
#   if defined(__cpp_lib_filesystem)
#       define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 0
#   elif defined(__cpp_lib_experimental_filesystem)
#       define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 1
#   elif !defined(__has_include)
#       define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 1
#   elif __has_include(<filesystem>)
#       ifdef _MSC_VER
#           if __has_include(<yvals_core.h>)
#               include <yvals_core.h>
#               if defined(_HAS_CXX17) && _HAS_CXX17
#                   define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 0
#               endif
#           endif
#           ifndef INCLUDE_STD_FILESYSTEM_EXPERIMENTAL
#               define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 1
#           endif
#       else
#           define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 0
#       endif
#   elif __has_include(<experimental/filesystem>)
#       define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 1
#   else
#       error Could not find system header "<filesystem>" or "<experimental/filesystem>"
#   endif
#   if INCLUDE_STD_FILESYSTEM_EXPERIMENTAL
#       include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#   else
#       include <filesystem>
#		if __APPLE__
namespace fs = std::__fs::filesystem;
#		else
namespace fs = std::filesystem;
#		endif
#   endif
#endif

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Definitions and Declarations
////////////////////////////////////////////////////////////////////////////////////////////////////
#define MULTITHREADED_ENABLED 1

enum class ESortType { AlphabeticalAscending, AlphabeticalDescending, LastLetterAscending };

std::mutex mtx;

class IStringComparer {
public:
	virtual bool IsFirstAboveSecond(string _first, string _second) = 0;
};

class AlphabeticalAscendingStringComparer : public IStringComparer {
public:
	bool IsFirstAboveSecond(string _first, string _second) override;
};


void DoSingleThreaded(vector<string> _fileList, ESortType _sortType, const string& _outputName);
void DoMultiThreaded(vector<string> _fileList, ESortType _sortType, const string& _outputName);
void ReadFile(const string& _fileName, vector<string>*);
void ThreadedReadFile(const string& _fileName, vector<string>* _listOut);
vector<string> BubbleSort(vector<string> _listToSort, ESortType _sortType);
void QuickSort(vector<string>& _listToSort, int left, int right, ESortType _sortType);
void WriteAndPrintResults(const vector<string>& _masterStringList, const string& _outputName, int _clocksTaken);
void QuickSort1(vector<string>& _listToSort, int left, int right, ESortType _sortType);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	// Enumerate the directory for input files

	vector<string> fileList;
	string inputDirectoryPath = "../InputFiles";
	
	// File input iterator sorted by the file names in the directory, and the 4 files in InputFiles are put into fileList
	for (const auto& entry : fs::directory_iterator(inputDirectoryPath)) {
		if (!fs::is_directory(entry)) {
			fileList.push_back(entry.path().string());
		}
	}

	string outputDirectoryPath = "../OutputFiles";

	// Do the stuff
	DoSingleThreaded(fileList, ESortType::AlphabeticalAscending, outputDirectoryPath + "/SingleAscending");
	DoSingleThreaded(fileList, ESortType::AlphabeticalDescending, outputDirectoryPath + "/SingleDescending");
	DoSingleThreaded(fileList, ESortType::LastLetterAscending, outputDirectoryPath + "/SingleLastLetter");
#if MULTITHREADED_ENABLED

	DoMultiThreaded(fileList, ESortType::AlphabeticalAscending, outputDirectoryPath + "/MultiAscending");
	DoMultiThreaded(fileList, ESortType::AlphabeticalDescending, outputDirectoryPath + "/MultiDescending");
	DoMultiThreaded(fileList, ESortType::LastLetterAscending, outputDirectoryPath + "/MultiLastLetter");
#endif

	// Wait
	cout << endl << "Finished...";
	getchar();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// The Stuff
////////////////////////////////////////////////////////////////////////////////////////////////////
void DoSingleThreaded(vector<string> _fileList, ESortType _sortType, const string& _outputName) {
	clock_t startTime = clock();
	vector<string> masterStringList;
	for (unsigned int i = 0; i < _fileList.size(); ++i) {
		// Abandon looping, and use addresses to reduce time complexity
		ReadFile(_fileList[i], &masterStringList);
		/*for (unsigned int j = 0; j < fileStringList.size(); ++j) {
			masterStringList.push_back(fileStringList[j]);
		}*/

		// Abandon BubbleSort and adopt faster Quicksort
		QuickSort(masterStringList, 0, masterStringList.size(), _sortType);
		QuickSort(masterStringList, 1, masterStringList.size(), _sortType);
		QuickSort(masterStringList, 2, masterStringList.size(), _sortType);
		if (_sortType == ESortType::LastLetterAscending)
		{
			for (int i = 0; i < masterStringList.size(); i++)
			{
				std::reverse(masterStringList[i].rbegin(), masterStringList[i].rend());

			}
			QuickSort1(masterStringList, 0, masterStringList.size(), _sortType);
			QuickSort1(masterStringList, 1, masterStringList.size(), _sortType);
			QuickSort1(masterStringList, 2, masterStringList.size(), _sortType);

			for (int i = 0; i < masterStringList.size(); i++)
			{
				std::reverse(masterStringList[i].rbegin(), masterStringList[i].rend());
			}
		}

	}
	clock_t endTime = clock();

	WriteAndPrintResults(masterStringList, _outputName, endTime - startTime);
}

void DoMultiThreaded(vector<string> _fileList, ESortType _sortType, const string& _outputName) {
	clock_t startTime = clock();
	vector<string> masterStringList;
	vector<thread> workerThreads(_fileList.size());

	// Build 4 threads
	for (unsigned int i = 0; i < _fileList.size(); ++i) {
		workerThreads[i] = thread(ThreadedReadFile, _fileList[i], &masterStringList);
		// A total of _fileList.size() threads are created, and only one thread will be created if outside the loop
		workerThreads[i].join();
	}

	//masterStringList = BubbleSort(masterStringList, _sortType);
	QuickSort(masterStringList, 0, masterStringList.size(), _sortType);
	QuickSort(masterStringList, 1, masterStringList.size(), _sortType);
	QuickSort(masterStringList, 2, masterStringList.size(), _sortType);

	if (_sortType == ESortType::LastLetterAscending)
	{
		for (int i = 0; i < masterStringList.size(); i++)
		{
			std::reverse(masterStringList[i].rbegin(), masterStringList[i].rend());
		}
		QuickSort1(masterStringList, 0, masterStringList.size(), _sortType);
		QuickSort1(masterStringList, 1, masterStringList.size(), _sortType);
		QuickSort1(masterStringList, 2, masterStringList.size(), _sortType);
		for (int i = 0; i < masterStringList.size(); i++)
		{
			std::reverse(masterStringList[i].rbegin(), masterStringList[i].rend());
		}
	}
	clock_t endTime = clock();

	WriteAndPrintResults(masterStringList, _outputName, endTime - startTime);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// File Processing
////////////////////////////////////////////////////////////////////////////////////////////////////
void ReadFile(const string& _fileName, vector<string>* masterStringList) {
	streampos positionInFile = 0;
	bool endOfFile = false;
	ifstream fileIn(_fileName);
	string tempString;
	while (getline(fileIn, tempString))
	{
		masterStringList->push_back(tempString);
	}

	// RAII - "Resource Acquisition Is Initialization"
	// Should not call close(), because if exception throwed may not close
	// fileIn.close();

}

void ThreadedReadFile(const string& _fileName, vector<string> *_listOut) {
    mtx.lock();
	// adopt_lock确实是跟收养了个锁差不多，在test5不带参数的这个函数中，先上锁，
	// 然后托管给lock_guard这个类，之后如果发生了异常阿也不需要没有解锁而产生死锁的现象
    std::lock_guard<std::mutex> lck(mtx, std::adopt_lock);
    ReadFile(_fileName, _listOut);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Sorting
////////////////////////////////////////////////////////////////////////////////////////////////////
bool AlphabeticalAscendingStringComparer::IsFirstAboveSecond(string _first, string _second) {
	unsigned int i = 0;
	while (i < _first.length() && i < _second.length()) {
		if (_first[i] < _second[i])
			return true;
		else if (_first[i] > _second[i])
			return false;
		++i;
	}
	return (i == _first.length());
}

vector<string> BubbleSort(vector<string> _listToSort, ESortType _sortType) {
	AlphabeticalAscendingStringComparer* stringSorter = new AlphabeticalAscendingStringComparer();
	vector<string> sortedList = _listToSort;
	for (unsigned int i = 0; i < sortedList.size() - 1; ++i) {
		for (unsigned int j = 0; j < sortedList.size() - 1; ++j) {
			if (!stringSorter->IsFirstAboveSecond(sortedList[j], sortedList[j + 1])) {
				string tempString = sortedList[j];
				sortedList[j] = sortedList[j + 1];
				sortedList[j + 1] = tempString;
			}
		}
	}
	return sortedList;
}

void QuickSort(vector<string>& _listToSort, int left, int right, ESortType _sortType)
{

	if (left >= right)
		return;
	int prev = left;
	int cur = left + 1;
	string key = _listToSort[left];

	while (cur < right)
	{
		{
			if (_sortType == ESortType::AlphabeticalAscending) {
				if (_listToSort[cur] < key && ++prev != cur)
					swap(_listToSort[prev], _listToSort[cur]);
			}
			if (_sortType == ESortType::AlphabeticalDescending)
			{
				if (_listToSort[cur] > key && ++prev != cur)
					swap(_listToSort[prev], _listToSort[cur]);
			}
		}
		++cur;
	}
	swap(_listToSort[left], _listToSort[prev]);
	QuickSort(_listToSort, left, prev - 1, _sortType);
	QuickSort(_listToSort, prev + 1, right, _sortType);
}

void QuickSort1(vector<string>& _listToSort, int left, int right, ESortType _sortType)
{
	if (left >= right)
		return;
	int prev = left;
	int cur = left + 1;
	string key = _listToSort[left];

	while (cur < right)
	{
		if (_sortType == ESortType::LastLetterAscending)
		{
			if (_listToSort[cur] < key && ++prev != cur)
				swap(_listToSort[prev], _listToSort[cur]);
		}

		++cur;
	}
	swap(_listToSort[left], _listToSort[prev]);
	QuickSort1(_listToSort, left, prev - 1, _sortType);
	QuickSort1(_listToSort, prev + 1, right, _sortType);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Output
////////////////////////////////////////////////////////////////////////////////////////////////////
void WriteAndPrintResults(const vector<string>& _masterStringList, const string& _outputName, int _clocksTaken) {
	cout << endl << _outputName << "\t- Clocks Taken: " << _clocksTaken << endl;

	ofstream fileOut(_outputName + ".txt", ofstream::trunc);
	for (unsigned int i = 0; i < _masterStringList.size(); ++i) {
		fileOut << _masterStringList[i] << endl;
	}
	fileOut.close();
}


// 搞错了，可能用 merge sort 更好
/*
1) QuickSort的时间复杂度平均是O(nlogn)，但最坏情况下是O(n^2)。
	MergeSort的时间复杂度严格来说就是O(nlogn)。
	那为什么实际应用中QuickSort用得多呢？
	因为MergeSort需用分配额外的O(n)空间，当用到new函数的时候会消耗很多的系统时间。另外像JAVA里面还要garbage collection又消耗一些时间。所以总体上来说MergeSort的overhead更大。
2) QuickSort的写法有很多种，每次取pivot可以从中间取，
	也可以从两边取，也可以弄个随机函数取。QuickSort也可以搞个额外空间。
	而MergeSort一定是从中间取。
3) QuickSort是不稳定算法，MergegSort是稳定算法。
这里稳定是指当数组有重复元素时，排序后的元素仍然能保持之前的顺序。
4) QuickSort和MergeSort的复杂度都可以按T(n)=2T(n/2)+O(n)来分析。
QuickSort先做O(n)的部分，再做2T(n/2)的部分。即先整体有序，再局部有序。
MergeSort先做2T(n/2)的部分，再做O(n)的部分。即先局部有序，再整体有序。
*/