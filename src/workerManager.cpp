#include "workerManager.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
#include <string>
void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); //用输出的方式打开文件 写文件
    //写入每个人的数据
    for (int i = 0; i < this->m_empnum; i++)
    {
        ofs << this->m_empArray[i]->ID << "\t"
            << this->m_empArray[i]->m_name << "\t"
            << this->m_empArray[i]->did << endl;
    }
    // close
    ofs.close();
}
WorkerManager::WorkerManager()
{
    // cout << "WorkerManager的构造函数" << endl;
    // file is not exit
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // read
    // file is not exit
    if (!ifs.is_open())
    {
        cout << "File is not exit" << endl;
        this->m_empnum = 0;
        this->m_empArray = NULL;
        this->m_fileisempty = true;
        ifs.close();
        return;
    }
    // file is exit,however nothing
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        cout << "File is empty" << endl;
        this->m_empnum = 0;
        this->m_empArray = NULL;
        this->m_fileisempty = true;
        ifs.close();
        return;
    }
    int num = this->get_number();
    cout << "人数：" << num << endl;
    this->m_empnum = num;
    //开辟空间
    this->m_empArray = new Worker *[num];
    //将文件中的数据，存到数组中
    this->init_emp();
    /*for (int i = 0; i < this->m_empnum; i++)
    {
        cout << "员工编号：" << this->m_empArray[i]->ID << endl;
        cout << "员工姓名：" << this->m_empArray[i]->m_name << endl;
        cout << "部门编号：" << this->m_empArray[i]->did << endl;
    }*/
}
WorkerManager::~WorkerManager()
{
    // cout << "WorkerManager的析构函数" << endl;
    if (this->m_empArray != NULL)
    {

        delete[] this->m_empArray;
        this->m_empArray = NULL;
    }
}
void WorkerManager::showmenu()
{

    cout << "-------------" << endl;
    cout << "Welcome" << endl;
    cout << "1.增加职工序列" << endl;
    cout << "2.显示职工信息" << endl;
    cout << "3.删除离职职工" << endl;
    cout << "4.修改职工信息" << endl;
    cout << "5.查找职工信息" << endl;
    cout << "6.按照编号排序" << endl;
    cout << "7.清空所有文档" << endl;
    cout << "0.退出管理程序" << endl;
    cout << "-------------" << endl;
}
void WorkerManager::exitsystem()
{
    cout << "E" << endl;
    system("pause");
    exit(0);
}
// addworker
void WorkerManager::add_emp()
{
    cout << "输入添加职工数量" << endl;
    int addnum = 0;
    cin >> addnum;
    if (addnum > 0)
    {
        // add
        // newspace
        int newsize = this->m_empnum + addnum;
        Worker **newspace = new Worker *[newsize];
        // copy to new space
        if (this->m_empArray != NULL)
        {
            for (int i = 0; i < this->m_empnum; i++)
            {
                newspace[i] = this->m_empArray[i];
            }
        }
        // addnew
        for (int i = 0; i < addnum; i++)
        {
            int id;
            string name;
            int depart;
            cout << "输入" << i + 1 << "员工编号:" << endl;
            cin >> id;
            cout << "输入" << i + 1 << "员工姓名:" << endl;
            cin >> name;
            cout << "1.普通职工" << endl
                 << "2.经理" << endl
                 << "3.老板" << endl;
            cin >> depart;
            Worker *worker = NULL;
            switch (depart)
            {
            case 1:
                worker = new Employee(id, name, depart);
                break;
            case 2:
                worker = new Manager(id, name, depart);
                break;
            case 3:
                worker = new Boss(id, name, depart);
                break;
            default:
                break;
            }
            // save to arr[]
            // m_empnum是原来的人数
            newspace[this->m_empnum + i] = worker;
        }
        // delete
        delete[] this->m_empArray;
        // change
        this->m_empArray = newspace;
        // change new
        this->m_empnum = newsize;
        cout << "success" << addnum << endl;
        this->m_fileisempty = false;
        this->save();
        system("pause");
        system("cls");
    }
    else
    {
        cout << "输入数据有误" << endl;
    }
}
// show worker
void WorkerManager::show_worker()
{
    //判断
    if (this->m_fileisempty)
    {
        cout << "文件不存在" << endl;
    }
    else
    {
        for (int i = 0; i < m_empnum; i++)
        {
            this->m_empArray[i]->showinformation();
        }
    }
    system("pause");
    system("cls");
}
void WorkerManager::delete_worker()
{
    if (this->m_fileisempty == true || this->m_empnum == 0)
    {
        cout << "文件不存在或文件为空" << endl;
    }
    else if (this->m_empnum != 0)
    {
        cout << "输入删除员工编码：";
        int id = 0;
        cin >> id;
        int index = this->isexist(id);
        if (index != -1)
        {
            //数据前移覆盖
            for (int i = index; i < this->m_empnum - 1; i++)
            {
                this->m_empArray[i] = this->m_empArray[i + 1];
            }
            this->m_empnum--; //更新数组人员个数
            if (this->m_empnum == 0)
            {
                this->m_fileisempty = true;
            }
            this->save();
            cout << "success" << endl;
        }
        else
        {
            cout << "输入员工编码错误" << endl;
        }
    }
    system("pause");
    system("cls");
}
void WorkerManager::change_worker()
{
    if (this->m_fileisempty)
    {
        cout << "文件不存在或文件为空" << endl;
    }
    else
    {
        cout << "输入修改职工的编号：";
        int id;
        cin >> id;
        int ret = this->isexist(id);
        if (ret != -1)
        {
            cout << "Successfully Find" << endl;
            cout << id << " \t" << this->m_empArray[ret]->m_name << endl;
            delete this->m_empArray[ret];
            int newid = 0;
            string newname = "";
            int dselect = 0;
            cout << "输入新的职工编号：";
            cin >> newid;
            cout << "输入新的姓名：";
            cin >> newname;
            cout << "1.普通职工" << endl
                 << "2.经理" << endl
                 << "3.老板" << endl;
            cin >> dselect;
            Worker *worker = NULL;
            switch (dselect)
            {
            case 1:
                worker = new Employee(newid, newname, dselect);
                break;
            case 2:
                worker = new Manager(newid, newname, dselect);
                break;
            case 3:
                worker = new Boss(newid, newname, dselect);
                break;
            default:
                break;
            }
            this->m_empArray[ret] = worker;
            cout << "success" << endl;
            this->save();
        }
        else
        {
            cout << "查无此人" << endl;
        }
    }
    system("pause");
    system("cls");
}
void WorkerManager::find_worker()
{
    if (this->m_fileisempty)
    {
        cout << "文件不存在或文件为空" << endl;
    }
    else
    {
        cout << "输入查找方式：" << endl;
        cout << "1.id查找" << endl;
        cout << "2.姓名查找" << endl;
        int s = 0;
        cin >> s;
        if (s == 1)
        {
            // id
            int id;
            cout << "id:";
            cin >> id;
            int ret = isexist(id);
            if (ret != -1)
            {
                cout << "successly find" << endl;
                this->m_empArray[ret]->showinformation();
            }
            else
            {
                cout << "Error" << endl;
            }
        }
        else if (s == 2)
        {
            // name
            string name;
            cout << "name:";
            cin >> name;
            bool find = false;
            for (int i = 0; i < m_empnum; i++)
            {
                if (this->m_empArray[i]->m_name == name)
                {
                    cout << "successfully find" << endl;
                    this->m_empArray[i]->showinformation();
                    find = true;
                }
            }
            if (find == false)
            {
                cout << "Error" << endl;
            }
        }
        else
        {
            cout << "Error" << endl;
        }
    }
    system("pause");
    system("cls");
}
void WorkerManager::sort_worker()
{
    if (this->m_fileisempty)
    {
        cout << "文件不存在或文件为空" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "选择排序方式：" << endl;
        cout << "1.以id进行升序" << endl;
        cout << "2.以id经行降序" << endl;
        int s = 0;
        cin >> s;
        for (int i = 0; i < this->m_empnum; i++)
        {
            int minormax = i; //声明最小值或最大值下标
            for (int j = i + 1; j < this->m_empnum; j++)
            {
                if (s == 1)
                {
                    if (this->m_empArray[minormax]->ID > this->m_empArray[j]->ID)
                    {
                        minormax = j;
                    }
                }
                else
                {
                    if (this->m_empArray[minormax]->ID < this->m_empArray[j]->ID)
                    {
                        minormax = j;
                    }
                }
            }

            if (i != minormax)
            {
                Worker *temp = this->m_empArray[i];
                this->m_empArray[i] = this->m_empArray[minormax];
                this->m_empArray[minormax] = temp;
            }
        }
        cout << "succefully sort" << endl;
        this->save();
        this->show_worker();
    }
}
void WorkerManager::clean_file()
{
    cout << "确认？" << endl
         << "1.确定 2.返回" << endl;
    int s = 0;
    cin >> s;
    if (s == 1)
    {
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();
        if (this->m_empArray != NULL)
        {
            for (int i = 0; i < this->m_empnum; i++)
            {
                delete this->m_empArray[i];
                this->m_empArray[i] = NULL;
            }
            //删除堆区数组指针
            delete[] this->m_empArray;
            this->m_empArray = NULL;
            this->m_empnum = 0;
            this->m_fileisempty = true;
            cout << "success" << endl;
        }
    }
    else
    {
        //
    }
    system("pause");
    system("cls");
}
//查找id函数
int WorkerManager::isexist(int ID)
{
    int index = -1;
    for (int i = 0; i < this->m_empnum; i++)
    {
        if (this->m_empArray[i]->ID == ID)
        {
            index = i;
            break;
        }
    }
    return index;
}
//得到系统人数
int WorkerManager::get_number()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int did;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> did)
    {
        num++;
    }
    return num;
}
void WorkerManager::init_emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int did;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> did)
    {
        Worker *worker = NULL;
        if (did == 1)
        {
            //普通员工
            worker = new Employee(id, name, did);
        }
        else if (did == 2)
        {
            //经理
            worker = new Manager(id, name, did);
        }
        else
        {
            worker = new Boss(id, name, did);
        }
        this->m_empArray[index] = worker;
        index++;
    }
    ifs.close();
}