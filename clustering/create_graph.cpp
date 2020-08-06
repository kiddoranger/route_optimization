#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int main()
{
    cout<<"Enter number of locations\n";
    int x;
    cin>>x;
    ofstream fout;
    fout.open("graph.txt");
    fout<<x<<endl;
    cout<<"Enter adjacency matrix\n";
    vector<vector<int>>adj(x,vector<int>(x));
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<x;j++)
        {
            cin>>adj[i][j];
        }
    }
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<x;j++)
        {
            fout<<adj[i][j]<<" ";
        }
        fout<<endl;
    }
    fout.close();
    
}