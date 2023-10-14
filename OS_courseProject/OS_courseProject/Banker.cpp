#include "Banker.h"

Banker::Banker()
{
	int processNum = 0, resourceNum = 0;
	cout << "请输入进程数和资源数：" << endl;
	cin >> processNum >> resourceNum;
	this->processNum = processNum;
	this->resourceNum = resourceNum;
	vector<int> tmp;
	int a;
	cout << "请输入Max矩阵" << "(" << processNum << "X" << resourceNum << ")：" << endl;

	for (int i = 0; i < processNum; i++)
	{
		for (int j = 0; j < resourceNum; j++)
		{
			cin >> a;
			tmp.push_back(a);
		}
		Max.push_back(tmp);
		tmp.clear();
	}
	tmp.clear();
	cout << endl;

	cout << "请输入Allocation矩阵" << "(" << processNum << "X" << resourceNum << ")：" << endl;
	for (int i = 0; i < processNum; i++)
	{
		for (int j = 0; j < resourceNum; j++)
		{
			cin >> a;
			tmp.push_back(a);
		}
		Allocation.push_back(tmp);
		tmp.clear();
	}
	tmp.clear();
	cout << endl;

	/*cout << "请输入Need矩阵：" << endl;
	for (int i = 0; i < processNum; i++)
	{
		for (int j = 0; j < resourceNum; j++)
		{
			cin >> a;
			tmp.push_back(a);
		}
		Need.push_back(tmp);
		tmp.clear();
	}
	tmp.clear();
	cout << endl;*/
	vector<vector<int>> Need(processNum, vector<int>(resourceNum));
	for (int i = 0; i < processNum; i++)
		for (int j = 0; j < resourceNum; j++)
			Need[i][j] = Max[i][j] - Allocation[i][j];
	this->Need = Need;

	cout << "请输入可用资源数Available" << "(" << resourceNum << ")：" << endl;
	for (int i = 0; i < resourceNum; i++)
	{
		cin >> a;
		Available.push_back(a);
	}
	///*for (int i = 0; i < processNum; i++)
	//	for (int j = 0; j < resourceNum; j++)
	//		cout << Max[i][j];
	//cout << endl;
	//for (int i = 0; i < processNum; i++)
	//	for (int j = 0; j < resourceNum; j++)
	//		cout << Allocation[i][j];
	//cout << endl;*/
	/*for (int i=0; i < processNum; i++)
	for (int j=0; j < resourceNum; j++)
			cout <<this->Need[i][j];*/
			/*system("cls");
			resourcePrint();*/
}

Banker::Banker(int processNum, int resourceNum, vector<vector<int>>& Max, vector<vector<int>>& Allocation, vector<int>& Available)
{
	this->processNum = processNum;
	this->resourceNum = resourceNum;
	this->Max = Max;
	this->Allocation = Allocation;
	this->Available = Available;
	vector<vector<int>> Need(processNum, vector<int>(resourceNum));
	for (int i = 0; i < processNum; i++)
		for (int j = 0; j < resourceNum; j++)
			Need[i][j] = Max[i][j] - Allocation[i][j];
	this->Need = Need;
	/*system("cls");
	resourcePrint();*/
}

int Banker::requestResource(int process_id, vector<int> req)
{
	cout << "开始分配：" << endl << endl;
	for (int i = 0; i < resourceNum; i++)
		if (req[i] > Need[process_id][i])
			return 1;
	for (int i = 0; i < resourceNum; i++)
		if (req[i] > Available[i])
			return 2;
	for (int i = 0; i < resourceNum; i++)	//分配资源
	{
		Available[i] -= req[i];
		Allocation[process_id][i] += req[i];
		Need[process_id][i] -= req[i];
	}
	resourcePrint();
	if (!isSafe(1))
	{
		for (int i = 0; i < resourceNum; i++)	//回收资源
		{
			Available[i] += req[i];
			Allocation[process_id][i] -= req[i];
			Need[process_id][i] += req[i];
		}
		return 3;
	}
	//下属代码看需求，如果是连续分配，则不需要恢复，如果只是尝试单词，即可恢复
	/*else
		for (int i = 0; i < resourceNum; i++)	//恢复
		{
			Available[i] += req[i];
			Allocation[process_id][i] -= req[i];
			Need[process_id][i] += req[i];
		}*/
	cout << "安全序列为：" << endl;
	for (const auto& r : result)
	{
		for (int i = 0; i < r.size(); i++)
		{
			cout << r[i] << " ";
			if (i != r.size() - 1)
				cout << "-> ";
		}
		cout << endl;
	}
	return 0;
}

bool Banker::isSafe()
{
	path.clear();
	result.clear();
	vector<int> work;
	work = Available;
	vector<bool> isChecked(processNum, false);
	isSafeRecursive(work, isChecked);
	if (result.empty())
		return false;
	return true;
}

void Banker::isSafeRecursive(vector<int>& work, vector<bool>& isChecked)
{
	bool hasFound = false;
	if (path.size() == processNum)
	{
		result.push_back(path);
		safePrint(print_num);
		add_printNum();
		return;
	}
	for (int i = 0; i < processNum; i++)
	{
		if (!isChecked[i])
		{
			for (int j = 0; j < resourceNum; j++)
			{
				if (Need[i][j] > work[j])
					break;
				if (j == resourceNum - 1)
				{
					for (int k = 0; k < resourceNum; k++)
						work[k] += Allocation[i][k];
					isChecked[i] = true;
					hasFound = true;
					path.push_back(i);
					resourcePrint(work, i, isChecked);
					isSafeRecursive(work, isChecked);
					path.pop_back();
					isChecked[i] = false;
					for (int k = 0; k < resourceNum; k++)
						work[k] -= Allocation[i][k];
				}
			}
		}
	}
	if (!hasFound)
		return;
}

void Banker::safePrint(int print_num)
{
	cout << "安全" << endl;
	cout << "安全序列为：" << endl;
	/*for (int i = 0; i < processNum; i++)
	{
		cout << result[i] << " ";
		if (i != processNum - 1)
			cout << "-> ";
	}*/
	for (int i = 0; i < result[print_num].size(); i++)
	{
		cout << result[print_num][i] << " ";
		if (i != result[print_num].size() - 1)
			cout << "-> ";
	}
	cout << endl << endl;;
	cout << "***********************************************************" << endl;
}

void Banker::add_printNum()
{
	print_num++;
}

void Banker::safePrint()
{
	cout << "安全" << endl << endl;
	cout << "安全序列为：" << endl;
	/*for (int i = 0; i < processNum; i++)
	{
		cout << result[i] << " ";
		if (i != processNum - 1)
			cout << "-> ";
	}*/
	for (const auto& r : result)
	{
		for (int i = 0; i < r.size(); i++)
		{
			cout << r[i] << " ";
			if (i != r.size() - 1)
				cout << "-> ";
		}
		cout << endl;
	}
	cout << endl;
}

void Banker::unsafePrint()
{
	cout << "不安全" << endl;
}

void Banker::resourcePrint()
{
	cout << "进程分配表" << endl;
	cout << "进程\\资源\tMax\t\tAllocation\tNeed" << endl;
	for (int i = 0; i < processNum; i++)
	{
		cout << "P" << i << "\t\t";
		for (int j = 0; j < resourceNum; j++) cout << Max[i][j] << " ";
		cout << "\t\t";
		for (int j = 0; j < resourceNum; j++) cout << Allocation[i][j] << " ";
		cout << "\t\t";
		for (int j = 0; j < resourceNum; j++) cout << Need[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << "Available" << endl;
	for (int j = 0; j < resourceNum; j++) cout << Available[j] << " ";
	cout << endl;
}

void Banker::resourcePrint(vector<int>& work, int id, vector<bool> isChecked)
{
	cout << "分配给进程 " << id << endl;
	cout << "未分配资源进程" << endl;
	cout << "进程\\资源\tMax\t\tAllocation\tNeed" << endl;
	for (int i = 0; i < processNum; i++)
	{
		if (!isChecked[i])
		{
			cout << "P" << i << "\t\t";
			for (int j = 0; j < resourceNum; j++) cout << Max[i][j] << " ";
			cout << "\t\t";
			for (int j = 0; j < resourceNum; j++) cout << Allocation[i][j] << " ";
			cout << "\t\t";
			for (int j = 0; j < resourceNum; j++) cout << Need[i][j] << " ";
			cout << endl;
		}
	}
	cout << "分配后Available：" << endl;
	for (int i = 0; i < resourceNum; i++)
		cout << work[i] << " ";
	cout << endl;
	cout << "--------------------------------------------------" << endl;
}

void Banker::resoucePrint(int pid)
{
	cout << "分配给进程 " << pid << endl;
	cout << "未分配资源进程" << endl;
	cout << "进程\\资源\tMax\t\tAllocation\tNeed" << endl;

}

void Banker::requestPrint(int i, int pid)
{
	if (i == 1)
		cout << "分配失败！请求的资源数超过最大值！" << endl;
	if (i == 2)
		cout << "分配失败！系统中尚无足够的资源满足P" << pid << "的请求" << endl;
	if (i == 3)
		cout << "分配失败！假定分配后，无法通过安全性检查！" << endl;
	if (i == 0)
		cout << "分配成功！" << endl;
}
bool Banker::isSafe(int a)
{
	path.clear();
	result.clear();
	vector<int> work;
	work = Available;
	vector<bool> isChecked(processNum, false);
	isSafeRecursive(work, isChecked,a);
	if (result.empty())
		return false;
	return true;
}
void Banker::isSafeRecursive(vector<int>& work, vector<bool>& isChecked, int a)
{
	bool hasFound = false;
	if (path.size() == processNum)
	{
		result.push_back(path);
		return;
	}
	for (int i = 0; i < processNum; i++)
	{
		if (!isChecked[i])
		{
			for (int j = 0; j < resourceNum; j++)
			{
				if (Need[i][j] > work[j])
					break;
				if (j == resourceNum - 1)
				{
					for (int k = 0; k < resourceNum; k++)
						work[k] += Allocation[i][k];
					isChecked[i] = true;
					hasFound = true;
					path.push_back(i);
					isSafeRecursive(work, isChecked,a);
					path.pop_back();
					isChecked[i] = false;
					for (int k = 0; k < resourceNum; k++)
						work[k] -= Allocation[i][k];
				}
			}
		}
	}
	if (!hasFound)
		return;
}





