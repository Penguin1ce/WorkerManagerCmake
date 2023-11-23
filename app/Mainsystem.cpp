#include <iostream>
#include "boss.h"
#include "employee.h"
#include "manager.h"
#include "worker.h"
#include "workerManager.h"
#define FILENAME "empfile.txt"
using namespace std;
int main()
{
	int s = 0;
	WorkerManager wk;
	while (true)
	{
		//��ʼ����
		wk.showmenu();
		cin >> s;
		switch (s)
		{
		case 0:
			//�˳�
			wk.exitsystem();
			break;
		case 1:
			// addperson
			wk.add_emp();
			break;
		case 2:
			// showperson
			wk.show_worker();
			break;
		case 3:
			// deleteperson
			wk.delete_worker();
			break;
		case 4:
			// changeperson
			wk.change_worker();
			break;
		case 5:
			// findperson
			wk.find_worker();
			break;
		case 6:
			// sortperson
			wk.sort_worker();
			break;
		case 7:
			// cleanperson
			wk.clean_file();
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}