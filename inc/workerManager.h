#pragma once
#include<iostream>
#include<fstream>
#include"worker.h"
#define FILENAME "empfile.txt"
using namespace std;
class WorkerManager
{
public:
	WorkerManager();
	//menu
	void showmenu();
	//exit
	void exitsystem();
	//remain worker's number
	int m_empnum;
	Worker** m_empArray;
	//add
	void add_emp();
	//save the file
	void save();
	//recognize 
	bool m_fileisempty;
	//ret worker's number
	int get_number();
	void init_emp();
	void show_worker();
	//delete worker we need to find this person
	//In order to find this guy,return 
	int isexist(int ID);
	void delete_worker();
	//change
	void change_worker();
	//find worker
	void find_worker();
	//sort
	void sort_worker();
	void clean_file();
	~WorkerManager();
};