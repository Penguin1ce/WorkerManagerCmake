#include <iostream>
using namespace std;
#include "employee.h"

Employee::Employee(int id, string name, int did)
{
	this->ID = id;
	this->m_name = name;
	this->did = did;
}
void Employee::showinformation()
{
	cout << "ְ����ţ�" << this->ID << endl;
	cout << "\t������" << this->m_name << endl;
	cout << "\t��λ:" << this->getdidname() << endl;
	cout << "\t��ɾ�����������" << endl;
}
string Employee::getdidname()
{
	return "Ա��";
}
