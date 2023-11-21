#include "boss.h"
Boss::Boss(int id, string name, int did)
{
	this->ID = id;
	this->m_name = name;
	this->did = did;
}
void Boss::showinformation()
{
	cout << "职工编号：" << this->ID << endl;
	cout << "\t姓名：" << this->m_name << endl;
	cout << "\t岗位:" << this->getdidname() << endl;
	cout << "\t管理公司事务" << endl;
}
string Boss::getdidname()
{
	return "总裁";
}