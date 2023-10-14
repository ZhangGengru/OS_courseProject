#pragma once
#include<iostream>
#include<array>
#include<vector>
#include<set>

using namespace std;

class Banker
{

public:
	Banker();
	Banker(int processNum, int resourceNum, vector<vector<int>>& Max, vector<vector<int>>& Allocation, vector<int>& Available);
	int requestResource(int process_id, vector<int> req);
	//bool checkSafe();
	bool isSafe();
	void safePrint();
	void unsafePrint();
	void resourcePrint();
	void resourcePrint(vector<int>& work, int id, vector<bool>isChecked);
	void resoucePrint(int pid);
	static void requestPrint(int i, int pid);
	inline int get_resourceNum() { return resourceNum; }
private:
	static int print_num;
	int processNum, resourceNum;
	vector<vector<int>> Max;
	vector<vector<int>> Allocation;
	vector<vector<int>> Need;
	vector<int> Available;
	void isSafeRecursive(vector<int>& work, vector<bool>& isChecked);
	bool hasFound = false;
	vector<int>path;
	vector<vector<int>> result;
	void safePrint(int print_num);
	static void add_printNum();
};