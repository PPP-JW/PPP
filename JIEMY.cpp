#include <iostream>
 
 using namespace std;
 
void create_RouteTable(int path[],int v)
 {
     int j=0,k=0;
     cout<<"Ŀ���������ڵ������   ��һ����ַ"<<endl;
     for(int i=0; i<n; i++)
     {
         int z=1;
         if(j!=v)
         {
             k=j;
             cout<<head[j].NetName<<" ";
             while(1)
             {
                 if(path[j]==v)
                 {
                     if(z!=1)
                     {
                         cout<<head[j].NetName<<endl;
                         break;
                     }
                    else
                     {
                         cout<<"ֱ�ӽ���"<<endl;
                         break;
                     }
                 }
                 else
                 {
                     j=path[j];
                     z++;
                }
            }
             j=k;
         }
        j++;
 
    }
 }