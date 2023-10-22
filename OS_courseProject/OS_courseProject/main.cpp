#include"Banker.h"
#include<string>

using namespace std;
int Banker::print_num = 0;

int main()
{
	//Banker myBank;
	vector<vector<int>> max{{7, 5, 3}, { 3,2,2 }, { 9,0,2 }, { 2,2,2 }, { 4,3,3 }};
	vector<vector<int>> alloc{{0, 1, 0}, { 2,0,0 }, { 3,0,2 }, { 2,1,1 }, { 0,0,2 }};
	vector<int> Avai{1,1,1};
	//vector<int> Avai{0,0,0};
	Banker myBank(5, 3, max, alloc, Avai);
	while (1)
	{
		myBank.resourcePrint();
		int switch_num = 0;
		cout << "\t\t\t\t请选择你要进行的操作：" << endl;
		cout << "\t\t\t\t1.对当前资源表进行安全性检查。" << endl;
		cout << "\t\t\t\t2.请求资源。" << endl;
		cout << "\t\t\t\t0.退出" << endl;
		cout << "\t\t\t请输入：";
		cin >> switch_num;
		cout << endl << endl;
		if (switch_num == 1)
		{
			if (myBank.isSafe())
			myBank.safePrint();
			else
				myBank.unsafePrint();
			system("pause");
			system("cls");
		}
		else if (switch_num == 2)
		{
			int a = 1;
			if (!myBank.isSafe(a))
			{
				system("cls");
				cout << "当前数据状态不安全，无法请求资源！"<<endl;
				continue;
			}
			cout << "安全，可以请求,";
			int pid = -1;
			string req;
			vector<int> request(3, 0);
			cout << "请输入请求资源号：";
			cin >> pid;
			cout << "请输入请求资源数： x...x 的形式" << "(1x" << myBank.get_resourceNum() << "矩阵)：";
			for (int i = 0; i < myBank.get_resourceNum(); i++)
				cin >> request[i];
			cout << endl;
			myBank.requestPrint(myBank.requestResource(pid, request), pid);
			system("pause");
			system("cls");
		}
		else if (switch_num == 0)
			break;
		else
		{
			cout << "请重新输入！" << endl;
			system("pause");
			system("cls");
		}
	}
	return 0;

}