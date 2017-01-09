#include <iostream>
 
 using namespace std;
 
void create_RouteTable(int path[],int v)
 {
     int j=0,k=0;
     cout<<"目的主机所在的网络号   下一跳地址"<<endl;
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
                         cout<<"直接交付"<<endl;
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