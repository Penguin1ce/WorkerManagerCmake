#pragma once
#include<iostream>
using namespace std;
//abstract worker
class Worker
{
public:
	virtual void showinformation() = 0;
	virtual string getdidname() = 0;
	int ID;
	string m_name;
	//department id
	int did;
};