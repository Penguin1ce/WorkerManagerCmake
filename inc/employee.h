#pragma once
#include<iostream>
#include"worker.h"
#include<string>
class Employee :public Worker
{
public:
	Employee(int id, string name, int did);
	virtual void showinformation();
	virtual string getdidname();
	
};