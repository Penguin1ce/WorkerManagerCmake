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
	cout << "职工编号：" << this->ID << endl;
	cout << "\t姓名：" << this->m_name << endl;
	cout << "\t岗位:" << this->getdidname() << endl;
	cout << "\t完成经理交给的任务" << endl;
}
string Employee::getdidname()
{
	return "员工";
}
