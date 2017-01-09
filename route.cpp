#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
using namespace std;
const int NumRoute = 100;
const int Maxsize = 20;
const int maxValue = 1000;
template <class T, class E>
struct RouteNet     //��Ϊ�߱���
{
	int dest;
	T dis;
	RouteNet<T, E> *Link;
};
template <class T, class E>
struct RouteList      //�������
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
	void Printf();                       //���Ժ����������ֵ
	void Print();              //���Ժ����������ֵ
	bool InsertRoute(const E *Routename, string A);     //����վ��
	bool InsertLine(char *a, char *b, T d);  //����·��
	bool DeleteLine(char *a, char *b);
	bool DeleteRoute(char *a);
	bool IsNear(int a, int b)
	{
		RouteNet<T, E> *p = head[a].next;
		while (p != NULL)
		{
			if (p->dest == b)
				return true;
			else
				p = p->Link;
		}
		return false;
	}
	int FindAddr(char*a);
	T getWeight(char*a, char*b);
	void ShortminPath(char*v, int distance[], int minPath[]);
	void create_RouteTable(int path[], char*m);
	E* GetValue(E *i)//����վ��i��ֵ
	{
		if (i == NULL)
		{
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
			return i;
	}
	return -1;
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
	strcpy(head[v].Routename, head[Num - 1].Routename);
	head[v].Netname = head[Num - 1].Netname;
	head[v].next = head[Num - 1].next; head[Num - 1].next = NULL;
	p = head[v].next;
	while (p != NULL)
	{
		s = head[p->dest].next;
		while (s != NULL){
			if (s->dest == Num - 1)
			{
				s->dest = v;
				break;

			}
			else
				s = s->Link;
		}
		p = p->Link;
	}
	Num--;
	return true;
}
template <class T, class E>
bool CreatNet<T, E>::DeleteLine(char *a, char *b)     //ɾ������ߣ�ģ��ȡ����վ��ͨ��·�ߣ�
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
bool CreatNet<T, E>::InsertLine(char *a, char *b, T d)     //�����ڽӱ�(ģ�ⴴ������ͨ�����)
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
	cout << "·����    �����  ����·����  dest  ����" << endl;
	for (int i = 0; i<Num; i++)
	{
		p = head[i].next;
		cout << head[i].Routename << endl;
		while (p != NULL)
		{
			cout << "     ----" << head[i].Netname << "----" << head[p->dest].Routename << " ---" << p->dest << "---" << p->dis << endl;
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
template<class T, class E>
T CreatNet<T, E>::getWeight(char*a, char*b)
{
	int i = FindAddr(a);
	int j = FindAddr(b);
	if (i != -1 && j != -1)
	{
		RouteNet<T, E>*p = head[i].next;
		while (p != NULL&&p->dest != j)
		{
			p = p->Link;
		}
		if (p != NULL)return p->dis;
	}
	return maxValue;
}
template<class T, class E>
void CreatNet<T, E>::create_RouteTable(int path[], char*m)
{

	int v = FindAddr(m);
	int j = 0, k = 0;
	//cout<<v<<endl;
	cout << "Ŀ���������ڵ������   ��һ����ַ" << endl;
	for (int i = 0; i<Num; i++)
	{
		int z = 1;
		if (i != v)
		{
			k = i;
			cout << "   " << head[i].Netname;
			if (IsNear(v, i) == true)
			{
				cout << "              ֱ�ӽ���" << endl;
			}
			else
			{
				while (1)
				{
					if (path[i] == v)
					{
						if (z != 1)
						{
							cout << "              " << head[i].Netname << endl;
							break;
						}
						else
						{
							cout << "              ֱ�ӽ���" << endl;
							break;
						}
					}
					else if (path[i] != v)
					{
						i = path[i];//cout<<i<<endl;
						z++;
						//cout<<z<<endl;
					}
				}
				i = k;
			}

		}
	}
}
template<class T, class E>
void CreatNet<T, E>::ShortminPath(char*v, int distance[], int minPath[])
{
	int n = Num;	//�������
	bool *S = new bool[n];

	int i, j, k, len, A;
	A = FindAddr(v);
	for (i = 0; i < n; i++)//��ʼ��
	{

		S[i] = false;

		distance[i] = getWeight(v, head[i].Routename);
		//cout<<distance[i]<<endl;

		if (i != A&& distance[i] < maxValue)

			minPath[i] = A;

		else minPath[i] = -1;

	}

	S[A] = true;		//�ӵ�
	distance[A] = 0;
	for (i = 0; i < n - 1; i++)//����������·��
	{
		int B = maxValue;//*************************************
		int u = A;//ѡ����S�о������·���Ķ���u
		for (int j = 0; j < n; j++)
		{
			//***********************************************
			if (S[j] == false && distance[j] < B)
			{
				u = j;
				B = distance[j];
			}
		}

		S[u] = true;
		for (k = 0; k < n; k++)
		{
			len = getWeight(head[u].Routename, head[k].Routename);

			if (S[k] == false && len < maxValue&&distance[u] + len< distance[k])//************************
			{
				distance[k] = distance[u] + len;
				minPath[k] = u;
			}
		}

		//********}***************************************
		// }
	}
}


int main()
{
	char ch;
	CreatNet<int, char> X, L;
	X.ReadRoute();
	X.ReadNet();
	cout << "�ѹ���·������ͼ��" << endl;
	X.Print();
	while (ch != 'F' || ch != 'f')
	{
		cout << "************************************" << endl;
		cout << "           ��ѡ�����ѡ��           " << endl;
		cout << "           A������·�ɣ�            " << endl;
		cout << "           B���������磺              " << endl;
		cout << "           C: ɾ�����磺              " << endl;
		cout << "           D��ɾ��·�ɣ�              " << endl;
		cout << "           E���鿴·�ɱ�              " << endl;
		cout << "           F: �˳����              " << endl;
		cout << "************************************" << endl;
		cin >> ch;
		if (ch == 'A' || ch == 'a')
		{
			cout << "������Ҫ�����·������(end������)" << endl;
			char *cho = "end";
			string A;
			char *arr = new char[10];
			cin >> arr;
			cout << "������·������������ţ�" << endl;
			cin >> A;
			while (strcmp(arr, cho) != 0)
			{
				if (X.InsertRoute(arr, A) == false)
					cout << "����ʧ�ܣ�" << endl;
				else
					cout << "����ɹ���" << endl;
				cout << "������Ҫ�����·������(end������)" << endl;
				cin >> arr;
				cout << "������·������������ţ�" << endl;
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
			cout << "������Ҫ�������������·��:" << endl;
			cin >> a >> b;
			cout << "��������վ�����(0����������)" << endl;
			cin >> c;
			while (c != 0)
			{
				if (X.InsertLine(a, b, c) == false)
					cout << "����ʧ�ܣ�" << endl;
				else
					cout << "����ɹ���" << endl;
				cout << "������Ҫ�������������·��:" << endl;
				cin >> a >> b;
				cout << "��������վ�����(0����������)" << endl;
				cin >> c;
			}
			X.Print();
		}
		if (ch == 'C' || ch == 'c')
		{
			char *a = new char[10];
			char *b = new char[10];
			char *cho = "end";
			cout << "������Ҫɾ�����������·��:(����end���˳�)" << endl;
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
		if (ch == 'E' || ch == 'e')
		{
			char *cho = "end";
			cout << "������Ҫ�鿴��·�ɱ��·��������(����end���˳�)" << endl;
			char *i = new char[10];
			cin >> i;
			int distance[NumRoute];
			int minPath[NumRoute];
			while (strcmp(i, cho) != 0)
			{
				X.ShortminPath(i, distance, minPath);
				X.create_RouteTable(minPath, i);
				cout << "������Ҫ�鿴��·�ɱ��·��������(����end���˳�)" << endl;
				cin >> i;
			}
		}
	}
}
