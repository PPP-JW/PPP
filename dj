#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
using namespace std;
const int NumRoute = 100;
const int Maxsize = 20;
template <class T, class E>
struct RouteNet     //��Ϊ�߱�����
{
	int dest;
	T dis;
	RouteNet<T, E> *Link;
};
template <class T, class E>
struct RouteList      //����������
{
	E *Routename;
	string Netname;
	RouteNet<T, E> *next;
};
template <class T, class E>
class CreatNet
{
public:
	~CreatNet();
	CreatNet(int sz = NumRoute);
	void ReadRoute();
	void ReadNet();
	void Printf();                       //���Ժ�����������ֵ
	void Print();              //���Ժ�����������ֵ
	bool InsertRoute(const E *Routename, string A);     //����վ��
	bool InsertLine(char *a, char *b, T d);  //����·��
	bool DeleteLine(char *a, char *b);
	bool DeleteRoute(char *a);
	int FindAddr(char*a);
	E* GetValue(E *i)//����վ��i��ֵ
	{
		if (i == NULL){
			return NULL;
		}
		else
			return i;
	}
protected:
	RouteNet<T, E> *ptr;
	RouteList<T, E> *head;
	T Num = 0;
	T NumLine = 0;
};
template <class T, class E>
CreatNet<T, E>::~CreatNet()
{
	for (int i = 0; i<Num; i++)
		delete[]head;
}
template <class T, class E>
CreatNet<T, E>::CreatNet(int sz)            //���캯��
{
	head = new RouteList<T, E>[sz];
	for (int i = 0; i<sz; i++)
	{
		head[i].Routename = new E[Maxsize];
		head[i].next = NULL;
	}
	ptr = new RouteNet<T, E>;
	ptr->Link = NULL;
}
template <class T, class E>
bool CreatNet<T, E>::InsertRoute(const E *name, string A)      //����վ��
{
	if (Num == NumRoute)
		return false;
	else
		strcpy(head[Num].Routename, name);
	head[Num].Netname = A;
	Num++;
	return true;
}
template <class T, class E>
int CreatNet<T, E>::FindAddr(char*a)
{
	int i = 0;
	for (i = 0; i<Num; i++)
	{
		if (strcmp(a, head[i].Routename) == 0)
			break;
	}
	return i;
}
template <class T, class E>
bool CreatNet<T, E>::DeleteRoute(char *a)           //ɾ��վ��
{
	int v;
	v = FindAddr(a);
	if (Num == 1 || v<0 || v>NumRoute)
		return false;
	RouteNet<T, E> *p, *s, *t;
	int k;
	while (head[v].next != NULL)
	{
		p = head[v].next;
		k = p->dest;
		s = head[k].next;
		t = NULL;
		while (s != NULL&&s->dest != v)
		{
			t = s;
			s = s->Link;
		}
		if (s != NULL)
		{
			if (t == NULL)
				head[k].next = s->Link;
			else
				t->Link = s->Link;
			delete s;
		}
		head[v].next = p->Link;
		delete p;
		NumLine--;
	}
	Num--;
	strcpy(head[v].Routename, head[Num].Routename);
	head[v].Netname = head[Num].Netname;
	p = head[v].next;
	head[v].next = head[Num].next;
	while (p != NULL)
	{
		s = head[p->dest].next;
		while (s != NULL)
		if (s->dest == Num)
		{
			s->dest = v;
			break;

		}
		else
			s = s->Link;
	}
	return true;
}
template <class T, class E>
bool CreatNet<T, E>::DeleteLine(char *a, char *b)     //ɾ�������ߣ�ģ��ȡ����վ��ͨ��·�ߣ�
{
	int j, i;
	j = FindAddr(a);
	i = FindAddr(b);
	if (i != -1 && j != -1)
	{
		RouteNet<T, E> *p = head[j].next;
		RouteNet<T, E> *q = NULL;
		RouteNet<T, E> *s = p;
		while (p != NULL&&p->dest != i)
		{
			q = p;
			p = p->Link;
		}
		if (p != NULL)
		{
			if (p == s)
				head[j].next = p->Link;
			else
				q->Link = p->Link;
			delete p;
		}
		else
			return false;
		p = head[i].next;
		q = NULL;
		s = p;
		while (p->dest != j)
		{
			q = p;
			p = p->Link;
		}
		if (p == s)
			head[i].next = p->Link;
		else
			q->Link = p->Link;
		delete p;
		return true;
	}
	return false;
}
template <class T, class E>
bool CreatNet<T, E>::InsertLine(char *a, char *b, T d)     //�����ڽӱ�(ģ�ⴴ������ͨ������)
{
	int j = 0;
	int i = 0;
	j = FindAddr(a);
	i = FindAddr(b);
	if (j >= 0 && j<Num&&i >= 0 && i<Num)
	{
		RouteNet<T, E> *q;
		RouteNet<T, E> *p = head[j].next;
		while (p != NULL&&p->dest != i)
		{
			p = p->Link;
		}
		if (p != NULL)
			return false;
		p = new RouteNet<T, E>;
		q = new RouteNet<T, E>;
		p->dis = d;
		p->dest = i;
		p->Link = head[j].next;
		head[j].next = p;
		q->dis = d;
		q->dest = j;
		q->Link = head[i].next;
		head[i].next = q;
		NumLine++;
		return true;
	}
	return 0;
}
template <class T, class E>
void CreatNet<T, E>::Print()
{
	RouteNet<T, E> *p;
	cout << "·����    ������   ��һ��  ����" << endl;
	for (int i = 0; i<Num; i++){
		p = head[i].next;
		cout << head[i].Routename << endl;
		while (p != NULL)
		{
			cout << "     ----" << head[i].Netname << "----" << head[p->dest].Routename << " ---" << p->dis << endl;
			p = p->Link;
		}
	}
}
template <class T, class E>
void CreatNet<T, E>::ReadRoute()
{
	char *cho = "end";
	ifstream infile;
	infile.open("GetRoute.txt");
	cout << "Reading from the file......." << endl;
	for (int i = 0; i<NumRoute; i++)
	{
		infile >> head[i].Routename;
		infile >> head[i].Netname;
		if (strcmp(head[i].Routename, cho) == 0)
			break;
		Num++;
	}
	infile.close();
}
template <class T, class E>
void CreatNet<T, E>::ReadNet()
{
	char *cho = "end";
	char data1[10], data2[10];
	int i;
	ifstream infile;
	infile.open("GetNet.txt");
	cout << "Reading from the file ........" << endl;
	for (int i = 0; i<NumRoute; i++)
	{
		infile >> data1;
		infile >> data2;
		infile >> i;
		if (i == 0)
			break;
		else
			InsertLine(data1, data2, i);
		NumLine++;
	}
	infile.close();
}
int main()
{
	char ch;
	CreatNet<int, char> X, L;
	X.ReadRoute();
	X.ReadNet();
	cout << "�ѹ���·������ͼ��" << endl;
	X.Print();
	while (ch != 'E' || ch != 'e'){
		cout << "************************************" << endl;
		cout << "           ��ѡ������ѡ��           " << endl;
		cout << "           A������·�ɣ�            " << endl;
		cout << "           B���������磺              " << endl;
		cout << "           C: ɾ�����磺              " << endl;
		cout << "           D��ɾ��·�ɣ�              " << endl;
		cout << "           E: �˳�����              " << endl;
		cout << "************************************" << endl;
		cin >> ch;
		if (ch == 'A' || ch == 'a'){
			cout << "������Ҫ������·������(end������)" << endl;
			char *cho = "end";
			string A;
			char *arr = new char[10];
			cin >> arr;
			cout << "������·�������������ţ�" << endl;
			cin >> A;
			while (strcmp(arr, cho) != 0)
			{
				if (X.InsertRoute(arr, A) == false)
					cout << "����ʧ�ܣ�" << endl;
				else
					cout << "�����ɹ���" << endl;
				cout << "������Ҫ������·������(end������)" << endl;
				cin >> arr;
				cout << "������·�������������ţ�" << endl;
				cin >> A;
			}
			X.Print();
		}
		if (ch == 'B' || ch == 'b')
		{
			char *name = new char[Maxsize];
			string Routename;
			char *a = new char[10];
			char *b = new char[10];
			int c;
			cout << "������Ҫ��������������·��:" << endl;
			cin >> a >> b;
			cout << "��������վ������(0����������)" << endl;
			cin >> c;
			while (c != 0)
			{
				if (X.InsertLine(a, b, c) == false)
					cout << "����ʧ�ܣ�" << endl;
				else
					cout << "�����ɹ���" << endl;
				cout << "������Ҫ��������������·��:" << endl;
				cin >> a >> b;
				cout << "��������վ������(0����������)" << endl;
				cin >> c;
			}
			X.Print();
		}
		if (ch == 'C' || ch == 'c')
		{
			char *a = new char[10];
			char *b = new char[10];
			char *cho = "end";
			cout << "������Ҫɾ������������·��:(����end���˳�)" << endl;
			cin >> a >> b;
			while ((strcmp(a, cho) != 0) || (strcmp(b, cho) != 0))
			{
				if (X.DeleteLine(a, b) == false)
					cout << "ɾ��ʧ�ܣ�" << endl;
				else
					cout << "ɾ���ɹ���" << endl;
				cout << "������Ҫɾ��·�ߵ�����·��:(����end���˳�)" << endl;
				cin >> a >> b;
			}
			X.Print();
		}
		if (ch == 'D' || ch == 'd')
		{
			char *cho = "end";
			cout << "������Ҫɾ����·�ɣ�(����end���˳�)" << endl;
			char *i = new char[10];
			cin >> i;
			while (strcmp(i, cho) != 0)
			{
				if (X.DeleteRoute(i) == false)
					cout << "ɾ��ʧ��!" << endl;
				else
					cout << "ɾ���ɹ���" << endl;
				cout << "������Ҫɾ����·�ɣ�(����end���˳�)" << endl;
				cin >> i;
			}
			X.Print();
		}
	}
}
