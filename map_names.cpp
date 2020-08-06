#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int main()
{
    fstream f;
    f.open("route.txt");
    int num_buses;
    f>>num_buses;
    fstream m;
    m.open("Mapping.txt");
    map<int,string>names;
    for(int i=0;i<29;i++)
    {
        string s;
        m>>s;
        m>>s;
        m>>s;
        s="";
        string y;
        while(y.compare("Bangalore")!=0)
        {
            m>>y;
            s+=y;
            s+=" ";
        }
        names[i]=s;
    }
    for(int i=0;i<num_buses;i++)
    {
        int cap;
        f>>cap;
        cout<<"Bus number "<<i+1<<endl;
        for(int j=0;j<cap;j++)
        {
            int s;
            f>>s;
            cout<<names[s]<<endl;
        }
        cout<<endl;
    }
}