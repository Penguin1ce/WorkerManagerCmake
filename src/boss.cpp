#include "boss.h"
Boss::Boss(int id, string name, int did)
{
	this->ID = id;
	this->m_name = name;
	this->did = did;
}
void Boss::showinformation()
{
	cout << "ְ����ţ�" << this->ID << endl;
	cout << "\t������" << this->m_name << endl;
	cout << "\t��λ:" << this->getdidname() << endl;
	cout << "\t����˾����" << endl;
}
string Boss::getdidname()
{
	return "�ܲ�";
}