#include"../inc/manager.h"
Manager::Manager(int id, string name, int did)
{
	this->ID = id;
	this->m_name = name;
	this->did = did;
}
void Manager::showinformation()
{
	cout << "职工编号：" << this->ID << endl;
	cout << "\t姓名：" << this->m_name << endl;
	cout << "\t岗位:" << this->getdidname() << endl;
	cout << "\t完成上司交给的任务，并且下发任务" << endl;
}
string Manager::getdidname()
{
	return "经理";
}