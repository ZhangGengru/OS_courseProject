#include "Banker.h"

Banker::Banker()
{
	int processNum = 0, resourceNum = 0;
	cout << "���������������Դ����" << endl;
	cin >> processNum >> resourceNum;
	this->processNum = processNum;
	this->resourceNum = resourceNum;
	vector<int> tmp;
	int a;
	cout << "������Max����" << "(" << processNum << "X" << resourceNum << ")��" << endl;

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

	cout << "������Allocation����" << "(" << processNum << "X" << resourceNum << ")��" << endl;
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

	/*cout << "������Need����" << endl;
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

	cout << "�����������Դ��Available" << "(" << resourceNum << ")��" << endl;
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
	cout << "��ʼ���䣺" << endl << endl;
	for (int i = 0; i < resourceNum; i++)
		if (req[i] > Need[process_id][i])
			return 1;
	for (int i = 0; i < resourceNum; i++)
		if (req[i] > Available[i])
			return 2;
	for (int i = 0; i < resourceNum; i++)	//������Դ
	{
		Available[i] -= req[i];
		Allocation[process_id][i] += req[i];
		Need[process_id][i] -= req[i];
	}
	resourcePrint();
	if (!isSafe(1))
	{
		for (int i = 0; i < resourceNum; i++)	//������Դ
		{
			Available[i] += req[i];
			Allocation[process_id][i] -= req[i];
			Need[process_id][i] += req[i];
		}
		return 3;
	}
	//�������뿴����������������䣬����Ҫ�ָ������ֻ�ǳ��Ե��ʣ����ɻָ�
	/*else
		for (int i = 0; i < resourceNum; i++)	//�ָ�
		{
			Available[i] += req[i];
			Allocation[process_id][i] -= req[i];
			Need[process_id][i] += req[i];
		}*/
	cout << "��ȫ����Ϊ��" << endl;
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
	cout << "��ȫ" << endl;
	cout << "��ȫ����Ϊ��" << endl;
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
	cout << "��ȫ" << endl << endl;
	cout << "��ȫ����Ϊ��" << endl;
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
	cout << "����ȫ" << endl;
}

void Banker::resourcePrint()
{
	cout << "���̷����" << endl;
	cout << "����\\��Դ\tMax\t\tAllocation\tNeed" << endl;
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
	cout << "��������� " << id << endl;
	cout << "δ������Դ����" << endl;
	cout << "����\\��Դ\tMax\t\tAllocation\tNeed" << endl;
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
	cout << "�����Available��" << endl;
	for (int i = 0; i < resourceNum; i++)
		cout << work[i] << " ";
	cout << endl;
	cout << "--------------------------------------------------" << endl;
}

void Banker::resoucePrint(int pid)
{
	cout << "��������� " << pid << endl;
	cout << "δ������Դ����" << endl;
	cout << "����\\��Դ\tMax\t\tAllocation\tNeed" << endl;

}

void Banker::requestPrint(int i, int pid)
{
	if (i == 1)
		cout << "����ʧ�ܣ��������Դ���������ֵ��" << endl;
	if (i == 2)
		cout << "����ʧ�ܣ�ϵͳ�������㹻����Դ����P" << pid << "������" << endl;
	if (i == 3)
		cout << "����ʧ�ܣ��ٶ�������޷�ͨ����ȫ�Լ�飡" << endl;
	if (i == 0)
		cout << "����ɹ���" << endl;
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





