#include"Banker.h"
#include<string>

using namespace std;
int Banker::print_num = 0;

int main()
{
	//Banker myBank;
	vector<vector<int>> max{{7, 5, 3}, { 3,2,2 }, { 9,0,2 }, { 2,2,2 }, { 4,3,3 }};
	vector<vector<int>> alloc{{0, 1, 0}, { 2,0,0 }, { 3,0,2 }, { 2,1,1 }, { 0,0,2 }};
	vector<int> Avai{3, 3, 2};
	Banker myBank(5, 3, max, alloc, Avai);
	/*myBank.resourcePrint();
	cout << "--------------------------------------------------" << endl;
	if (myBank.isSafe())
		myBank.safePrint();
	else
		myBank.unsafePrint();
	Banker::requestPrint(myBank.requestResource(2, { 1,0,0 }), 2);
	Banker::requestPrint(myBank.requestResource(4, { 3,3,1 }), 4);*/
	while (1)
	{
		myBank.resourcePrint();
		int switch_num = 0;
		cout << "\t\t\t\t��ѡ����Ҫ���еĲ�����" << endl;
		cout << "\t\t\t\t1.�Ե�ǰ��Դ����а�ȫ�Լ�顣" << endl;
		cout << "\t\t\t\t2.������Դ��" << endl;
		cout << "\t\t\t\t0.�˳�" << endl;
		cout << "\t\t\t�����룺";
		cin >> switch_num;
		cout << endl << endl;
		if (switch_num == 1)
		{
			if (myBank.isSafe());
			//myBank.safePrint();
			else
				myBank.unsafePrint();
			system("pause");
			system("cls");
		}
		else if (switch_num == 2)
		{
			int pid = -1;
			string req;
			vector<int> request(3, 0);
			cout << "������������Դ�ţ�";
			cin >> pid;
			cout << "������������Դ���� x...x ����ʽ" << "(1x" << myBank.get_resourceNum() << "����)��";
			for (int i = 0; i < myBank.get_resourceNum(); i++)
				cin >> request[i];
			cout << endl;
			Banker::requestPrint(myBank.requestResource(pid, request), pid);
			system("pause");
			system("cls");
		}
		else if (switch_num == 0)
			break;
		else
		{
			cout << "���������룡" << endl;
			system("pause");
			system("cls");
		}
	}
	return 0;

}