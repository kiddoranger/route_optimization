#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int main(int argc,char** argv)
{   fstream m;
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
    
    fstream route,f;
    int start_h=atoi(argv[1]);
    int start_m=atoi(argv[2]);
    route.open("route.txt");
    f.open("time_matrix.txt");
    int n;
    f>>n;
    vector<vector<long double>>adj(n,vector<long double>(n));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            f>>adj[i][j];
        }
    }
    vector<double> end_point(n);
    for(int i=0;i<n;i++)
    {
        f>>end_point[i];
    }
    int num_buses;
    route>>num_buses;
    cout<<"The boarding times are:"<<endl;
    for(int i=0;i<num_buses;i++)
    {
        int cap;
        route>>cap;
        vector<int>hour(cap+1,start_h);
        vector<int>minute(cap+1,start_m);
        vector<int>p(cap);
        for(int j=0;j<cap;j++)
        {
            route>>p[j];
        }
        for(int j=1;j<cap;j++)
        {
            int prev=p[j-1];
            int curr=p[j];
            minute[j]=int((minute[j-1]+adj[prev][curr]))%60;
            hour[j]=int((hour[j-1]+((minute[j-1]+adj[prev][curr])/60)))%24;
        }
        minute[cap] = int((minute[cap-1]+end_point[p[cap-1]]))%60;
        hour[cap]=int((hour[cap-1]+((minute[cap-1]+end_point[p[cap-1]])/60)))%24;
        cout<<"Bus number "<<i+1<<endl;
        for(int j=0;j<cap;j++)
        {
            cout<<names[p[j]]<<"= "<<hour[j]<<":"<<minute[j]<<endl;
        }
        cout<<"Bosch Bidadi= "<<hour[cap]<<":"<<minute[cap]<<endl;
    }
    route.close();
    f.close();
}