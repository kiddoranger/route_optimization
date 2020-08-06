#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int main(int argc,char** argv)
{
    fstream f;
    f.open("graph.txt");
    int n;
    f>>n;
    vector<vector<int>>adj(n,vector<int>(n));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            f>>adj[i][j];
        }
    }
    long double speed=atof(argv[1]);
    long double sp_in_ms=5*speed/18;
    vector<vector<double>>time(n,vector<double>(n));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            time[i][j]=((double)adj[i][j])/sp_in_ms;
        }
    }
    fstream fout;
    fout.open("time_matrix.txt");
    fout<<n<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            fout<<ceil(time[i][j]/60)<<" ";
        }
        fout<<endl;
    }

    for(int i=0;i<n;i++)
    {
        int j;
        f>>j;
        cout<<j<<endl;
        fout<<ceil(ceil(((double)j)/sp_in_ms)/60)<<" ";
        cout<<ceil(ceil(((double)j)/sp_in_ms)/60)<<" ";
    
    }
}