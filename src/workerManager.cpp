#include "workerManager.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
#include <string>
void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); //������ķ�ʽ���ļ� д�ļ�
    //д��ÿ���˵�����
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
    // cout << "WorkerManager�Ĺ��캯��" << endl;
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
    cout << "������" << num << endl;
    this->m_empnum = num;
    //���ٿռ�
    this->m_empArray = new Worker *[num];
    //���ļ��е����ݣ��浽������
    this->init_emp();
    /*for (int i = 0; i < this->m_empnum; i++)
    {
        cout << "Ա����ţ�" << this->m_empArray[i]->ID << endl;
        cout << "Ա��������" << this->m_empArray[i]->m_name << endl;
        cout << "���ű�ţ�" << this->m_empArray[i]->did << endl;
    }*/
}
WorkerManager::~WorkerManager()
{
    // cout << "WorkerManager����������" << endl;
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
    cout << "1.����ְ������" << endl;
    cout << "2.��ʾְ����Ϣ" << endl;
    cout << "3.ɾ����ְְ��" << endl;
    cout << "4.�޸�ְ����Ϣ" << endl;
    cout << "5.����ְ����Ϣ" << endl;
    cout << "6.���ձ������" << endl;
    cout << "7.��������ĵ�" << endl;
    cout << "0.�˳��������" << endl;
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
    cout << "�������ְ������" << endl;
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
            cout << "����" << i + 1 << "Ա�����:" << endl;
            cin >> id;
            cout << "����" << i + 1 << "Ա������:" << endl;
            cin >> name;
            cout << "1.��ְͨ��" << endl
                 << "2.����" << endl
                 << "3.�ϰ�" << endl;
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
            // m_empnum��ԭ��������
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
        cout << "������������" << endl;
    }
}
// show worker
void WorkerManager::show_worker()
{
    //�ж�
    if (this->m_fileisempty)
    {
        cout << "�ļ�������" << endl;
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
        cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
    }
    else if (this->m_empnum != 0)
    {
        cout << "����ɾ��Ա�����룺";
        int id = 0;
        cin >> id;
        int index = this->isexist(id);
        if (index != -1)
        {
            //����ǰ�Ƹ���
            for (int i = index; i < this->m_empnum - 1; i++)
            {
                this->m_empArray[i] = this->m_empArray[i + 1];
            }
            this->m_empnum--; //����������Ա����
            if (this->m_empnum == 0)
            {
                this->m_fileisempty = true;
            }
            this->save();
            cout << "success" << endl;
        }
        else
        {
            cout << "����Ա���������" << endl;
        }
    }
    system("pause");
    system("cls");
}
void WorkerManager::change_worker()
{
    if (this->m_fileisempty)
    {
        cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
    }
    else
    {
        cout << "�����޸�ְ���ı�ţ�";
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
            cout << "�����µ�ְ����ţ�";
            cin >> newid;
            cout << "�����µ�������";
            cin >> newname;
            cout << "1.��ְͨ��" << endl
                 << "2.����" << endl
                 << "3.�ϰ�" << endl;
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
            cout << "���޴���" << endl;
        }
    }
    system("pause");
    system("cls");
}
void WorkerManager::find_worker()
{
    if (this->m_fileisempty)
    {
        cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
    }
    else
    {
        cout << "������ҷ�ʽ��" << endl;
        cout << "1.id����" << endl;
        cout << "2.��������" << endl;
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
        cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "ѡ������ʽ��" << endl;
        cout << "1.��id��������" << endl;
        cout << "2.��id���н���" << endl;
        int s = 0;
        cin >> s;
        for (int i = 0; i < this->m_empnum; i++)
        {
            int minormax = i; //������Сֵ�����ֵ�±�
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
    cout << "ȷ�ϣ�" << endl
         << "1.ȷ�� 2.����" << endl;
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
            //ɾ����������ָ��
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
//����id����
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
//�õ�ϵͳ����
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
            //��ͨԱ��
            worker = new Employee(id, name, did);
        }
        else if (did == 2)
        {
            //����
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