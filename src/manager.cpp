#include "manager.h"
Manager::Manager(int id, string name, int did)
{
	this->ID = id;
	this->m_name = name;
	this->did = did;
}
void Manager::showinformation()
{
	cout << "ְ����ţ�" << this->ID << endl;
	cout << "\t������" << this->m_name << endl;
	cout << "\t��λ:" << this->getdidname() << endl;
	cout << "\t�����˾���������񣬲����·�����" << endl;
}
string Manager::getdidname()
{
	return "����";
}