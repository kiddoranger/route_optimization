#include<bits/stdc++.h>
#include<fstream>
#include<algorithm>
#include<stdlib.h>
using namespace std;
vector<vector<int>>adj;

int n;
int k;
int cap;
vector<int>dest;
void init_adj()
{
    fstream fin;
    int x;
    fin.open("graph.txt");
    fin>>x;
    adj.resize(x,vector<int>(x));
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<x;j++)
        {
            fin>>adj[i][j];
        }
    }

}
set<int>gen_centroids(int n,int k)
{
    vector<int>a;
    for(int i=0;i<n;i++)
    {
        a.push_back(i);
    }
    vector<int>out;
    std::sample(a.begin(),a.end(),std::back_inserter(out),k,std::mt19937{std::random_device{}()});
    set<int>s;
    for(auto i:out)
    {
        s.insert(i);
    }   
    return s;
}

map<int,vector<int>> ranking(set<int>& cent,set<int>& points)
{
    map<int,vector<int>> m;
    
    for(auto i:points)
    {
        vector<pair<int,int>>temp;
        for(auto c:cent)
        {
            temp.push_back(make_pair(adj[i][c],c));
        }
        sort(temp.begin(),temp.end());
        for(auto j:temp)
        {
            m[i].push_back(j.second);
        }
    }
    return m;
}

vector<set<int>> calc_clusters(set<int>& cent,int cap)
{
    vector<int>assignments(n,-1);
    map<int,set<pair<int,int>>>match;
    map<int,vector<int>>ranks;
    for(auto i:cent)
    {
        assignments[i]=i;
    }
    set<int>remaining;
    for(int i=0;i<n;i++)
    {
        if(assignments[i]==-1)
        {
            remaining.insert(i);
        }
    }    
    ranks=ranking(cent,remaining);
   
    while(!remaining.empty())
    {
        set<int>temp;
        for(auto i:remaining)
        {
            temp.insert(i);
        }
        for(auto i:temp)
        {
            for(auto j:ranks[i])
            {
                if(match[j].size()<cap)
                {
                    match[j].insert(make_pair(adj[j][i],i));
                    remaining.erase(i);
                    break;
                }
                else
                {
                    auto l=*(match[j].rbegin());
                    int max_dist=l.first;
                    if(adj[j][i]<max_dist)
                    {
                        match[j].erase(l);
                        remaining.insert(l.second);
                        match[j].insert(make_pair(adj[j][i],i));
                        remaining.erase(i);
                        break;
                    }
                    
                    
                }
                
            }
        }
        


    }
    for(auto i:cent)
    {
        match[i].insert(make_pair(i,i));
    }
    vector<set<int>>s;
    for(auto i:match)
    {
        set<int>temp;
        for(auto j:i.second)
        {
            temp.insert(j.second);
        }
        s.push_back(temp);
        temp.clear();
    }
    return s;
}
// int get_center(set<int>s)
// {
//     map<int,vector<int>>m=ranking(s,s);
//     int mini=10000000;
//     int minin=-1;
//     for(auto i:m)
//     {
//         int x=i.first;
//         int y=*(i.second.rbegin());
//        // int z=dest[x];
//         //y=max(y,z);
//         if(y<mini)
//         {
//             mini=y;
//             minin=x;
//         }
//     }
//     return minin;

// }
int get_center(set<int> s)
{
    int mini=100000000;
    int minin=-1;
    for(auto i:s)
    {
        int sum=0;
        for(auto j:s)
            sum+=adj[i][j];
        if(sum<mini)
        {
            mini=sum;
            minin=i;
        }
    }
    return minin;
}
set<int>recenter(vector<set<int>>assignments)
{
    set<int> cent;
    for(auto i:assignments)
    {
        cent.insert(get_center(i));
    }
    return cent;
}

void print_clusters(vector<set<int>>assignments)
{
    ofstream x;
    x.open("CLUSTERS.txt");
    int s=assignments.size();
    x<<s<<endl;

    for(auto i:assignments)
    {
        set<int> s=i;
        cout<<i.size()<<endl;
        for(auto j:s)
        {
            if(i.find(j)!=i.end()){
            for(int k=0;k<n;k++)
            {
                if(adj[j][k]<100&&j!=k)
                {
                    i.erase(k);
                }
            }
            }

        }
         x<<i.size()<<endl;
         for(auto j:i)
         {
             x<<j<<" ";
         }
        
        x<<endl;
    }
}
void init_dest()
{
    fstream f;
    f.open("dest.txt");
    dest.resize(n,0);
    for(int i=0;i<n;i++)
    {
        f>>dest[i];
    }
}

int main(int argc,char** argv)
{
    init_adj();
    n=adj[0].size();
    init_dest();
    k=atoi(argv[1]);
    cap=atoi(argv[2])-1;
    int num_it=atoi(argv[3]);
    set<int>cent=gen_centroids(n,k);
    
    for(int i=0;i<num_it;i++)
    {
        vector<set<int>>assignments=calc_clusters(cent,cap);
      
      
      
       /* for(int i=0;i<assignments.size();i++)
        {
            cout<<"Bus number "<<i<<endl;
            for(auto j:assignments[i])
            {
                cout<<j<<" ";
            }
            cout<<endl;
        }*/



        cent=recenter(assignments);
    

        if(i==num_it-1)
        {
            print_clusters(assignments);
        }
    }
}