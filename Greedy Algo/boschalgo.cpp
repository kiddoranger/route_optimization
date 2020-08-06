#include <bits/stdc++.h>
#include <sstream>
#include<ctime>
using namespace std;
#define ll long long int
#define ld long double
#define key pair<ld,ld>
#define ii pair<int,int>
#define si set<int>
#define mii map<int,int>
#define vii vector<pair<int,int> >
#define vi vector<int>
#define vll vector<ll>
#define vb vector<bool>
#define vvi vector<vector<int> >
#define vs vector<string>
#define all(v) v.begin(),v.end()
#define rep(i,l,r) for(int i=l;i<r;i++) 
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define nu 100001
#define mod 1000000007 
#define mul(x,y) ((ll)(x)*(y))%mod
#define tr(c,i) for(auto i = (c).begin(); i != (c).end(); i++)
#define fastio  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define INF 0x3f3f3f3f
ll MOD(ll a, ll b)
{
    if(a>b)
    return a-b;
    else
    return b-a;
}
ll power(ll x,ll y, ll p)
{
    ll res = 1;      
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res*x)%p;
        y = y>>1; 
        x = (x*x)%p;  
    }
    return res;
}
ll logg(ll a)
{
    ll x=0;
    while(a>1)
    {
        x++;
        a/=2;
    }
    return x;

}
pair<vector<int>,pair<int,double> > compute_min_path(pair<vector<int>,pair<int,double> >  bus1, pair<vector<int>,pair<int,double> >  bus2, vector<vector<double> >& adj_mat,vector<double>& end_dis)
{           
    int newcap = bus1.s.f+bus2.s.f;
    vector<vector<pair<double,int> > >dp(bus2.f.size(),vector<pair<double,int> >(bus1.f.size()+1)),dp1(bus2.f.size(),vector<pair<double,int> >(bus1.f.size()+1));
    vector<double> cumsum(bus1.f.size()+1);
    cumsum[0]=0;
    cumsum[1]=0;
    for(int i=2;i<bus1.f.size()+1;i++)
    {
        cumsum[i]=cumsum[i-1]+adj_mat[bus1.f[i-2]][bus1.f[i-1]];
    }
    for(int i=0;i<bus2.f.size();i++)
    {
        for(int j=0;j<bus1.f.size()+1;j++)
        {
            if(i==0)
            {
                if(j==0)
                {
                    dp[i][j]=mp(1000000000000,0);
                    dp1[i][j]=mp(0,-1);
                }
                else if(j<bus1.f.size())
                {
                    dp[i][j]=min(mp(dp[i][j-1].f+adj_mat[bus1.f[j-1]][bus1.f[j]],dp[i][j-1].s),mp(dp1[i][j-1].f+adj_mat[bus2.f[i]][bus1.f[j-1]]+adj_mat[bus1.f[j-1]][bus1.f[j]],j-1));
                    dp1[i][j]=mp(cumsum[j]+adj_mat[bus1.f[j-1]][bus2.f[i]],-1);
                }
                else
                {
                    dp[i][j]=min(mp(dp[i][j-1].f+end_dis[bus1.f[j-1]],dp[i][j-1].s),mp(dp1[i][j-1].f+end_dis[bus1.f[j-1]]+adj_mat[bus2.f[i]][bus1.f[j-1]],j-1));
                    dp1[i][j]=mp(cumsum[j]+adj_mat[bus1.f[j-1]][bus2.f[i]],-1);
                }
                
            }
            else
            {
                if(j==0)
                {
                    dp[i][j]=mp(1000000000000,0);
                    dp1[i][j]=mp(dp1[i-1][j].f+adj_mat[bus2.f[i-1]][bus2.f[i]],j);
                }
                else if(j<bus1.f.size())
                {
                    dp[i][j]=min(mp(dp[i][j-1].f+adj_mat[bus1.f[j-1]][bus1.f[j]],dp[i][j-1].s),mp(dp1[i][j-1].f+adj_mat[bus1.f[j-1]][bus1.f[j]]+adj_mat[bus2.f[i]][bus1.f[j-1]],j-1));
                    dp1[i][j]=min(mp(dp[i-1][j].f-adj_mat[bus1.f[j-1]][bus1.f[j]]+adj_mat[bus1.f[j-1]][bus2.f[i]],dp[i-1][j].s),mp(dp1[i-1][j].f+adj_mat[bus2.f[i-1]][bus2.f[i]],j));
                }
                else
                {
                    dp[i][j]=min(mp(dp[i][j-1].f+end_dis[bus1.f[j-1]],dp[i][j-1].s),mp(dp1[i][j-1].f+end_dis[bus1.f[j-1]]+adj_mat[bus2.f[i]][bus1.f[j-1]],j-1));
                    dp1[i][j]=min(mp(dp[i-1][j].f-end_dis[bus1.f[j-1]]+adj_mat[bus1.f[j-1]][bus2.f[i]],dp[i-1][j].s),mp(dp1[i-1][j].f+adj_mat[bus2.f[i-1]][bus2.f[i]],j));
                }    
            }
            // if(flag==2)
            //     cout<<"("<<dp[i][j].f<<" , "<<dp[i][j].s<<") ";
        }
        // if(flag==2)
        //     cout<<endl;
    }
    // cout<<bus1.s.s<<' '<<bus2.s.s<<endl;
    // cout<<dp[bus2.f.size()-1][bus1.f.size()].f<<" "<<dp1[bus2.f.size()-1][bus1.f.size()].f+end_dis[bus2.f[bus2.f.size()-1]];
    // exit(0);
    double min_distance = min(dp[bus2.f.size()-1][bus1.f.size()].f,dp1[bus2.f.size()-1][bus1.f.size()].f+end_dis[bus2.f[bus2.f.size()-1]]);
    int st;
    if(dp[bus2.f.size()-1][bus1.f.size()].f<dp1[bus2.f.size()-1][bus1.f.size()].f+end_dis[bus2.f[bus2.f.size()-1]])
    {
        st=dp[bus2.f.size()-1][bus1.f.size()].s;
    }
    else
    {
        st=bus1.f.size();
    }
    vector<int> new_route;
    int ct=bus2.f.size()-1;
    while(st!=-1)
    {
        new_route.push_back(st);
        st=dp1[ct][st].s;
        ct--;
    }
    reverse(all(new_route));
    vector<int> new_vector;
    int j=0;
    for(int i=0;i<bus1.f.size();i++)
    {
        while(j<bus2.f.size()&&new_route[j]==i)
        {
            new_vector.push_back(bus2.f[j]);
            j++;
        }
        new_vector.push_back(bus1.f[i]);
    }
    while(j<bus2.f.size())
    {
        new_vector.push_back(bus2.f[j]);
        j++;
    }
    return mp(new_vector,mp(newcap,min_distance));
}   
int main()
{
    fastio;
	int num_node,cap,max_dis;
    cout<<"Enter Number of non end points: ";
    cout<<flush;
    cin>>num_node;
    cout<<"Enter Capacity of a Bus: ";
    cout<<flush;
    cin>>cap;
    cout<<"Enter Max Distance one Bus can travel: ";
    cout<<flush;
    cin>>max_dis;
    cout<<"Enter Distances of the form of a matrix such that (i,j)th entry corresponds to the distance between ith and jth point:\n";
    cout<<flush;
    vector<vector<double> > adj_mat(num_node,vector<double>(num_node));
    for(int i=0;i<num_node;i++)
    {
        for(int j=0;j<num_node;j++)
        {
            cin>>adj_mat[i][j];
        }
    }
    cout<<"Enter Distance of each point to the end point in order:\n";
    cout<<flush;
    vector<double> end_dis(num_node);
    for(int i=0;i<num_node;i++)
        cin>>end_dis[i];
    vector<pair<vector<int>,pair<int,double> > > buses;
    double tot_dist = 0;
    for(int i=0;i<num_node;i++)
    {
        vector<int> trivial_path;
        trivial_path.push_back(i);
        buses.push_back(mp(trivial_path,mp(1,end_dis[i])));
        tot_dist+=end_dis[i];
    }
    vector<pair<vector<pair<vector<int>,pair<int,double> > > , double > > solutions(num_node+1);
    int n = num_node-1;
    solutions[n+1]=mp(buses,tot_dist);
    while(n>0)
    {
        int min_val,pos1,pos2,done=0;
        pair<vector<int>,pair<int,double> > newbuses,temp;
        for(int i=0;i<solutions[n+1].f.size();i++)
        {
            for(int j=0;j<solutions[n+1].f.size();j++)
            {
                if(i!=j)
                {
                    temp=compute_min_path(solutions[n+1].f[i],solutions[n+1].f[j],adj_mat,end_dis);
                    if(temp.s.f>cap||temp.s.s>max_dis)
                        continue;
                    if(done==0||(temp.s.s-solutions[n+1].f[i].s.s-solutions[n+1].f[j].s.s<min_val))
                    {
                        min_val = temp.s.s-solutions[n+1].f[i].s.s-solutions[n+1].f[j].s.s;
                        pos1=i;
                        pos2=j;
                        done=1;
                        newbuses = temp;
                    }
                    
                }
            }
        }
        if(done==0)
            break;
        else
        {
            int remove_min_pos=min(pos1,pos2),remove_max_pos=max(pos1,pos2);
            buses.erase(buses.begin()+remove_max_pos);
            buses.erase(buses.begin()+remove_min_pos);
            buses.push_back(newbuses);
            solutions[n]=mp(buses,solutions[n+1].s+min_val);
        }
        n--;
    }
    int least_bus = n+1;
    for(int i=least_bus;i<=num_node;i++)
    {
        cout<<"Num Buses: "<<i<<endl;
        for(int j=0;j<solutions[i].f.size();j++)
        {
            cout<<"\tBus Number: "<<j+1<<endl;
            cout<<"\t\tRoute: ";
            for(int k=0;k<solutions[i].f[j].f.size();k++)
            {
                cout<<solutions[i].f[j].f[k]<<' ';
            }
            cout<<endl;
            cout<<"\t\tCapacity: "<<solutions[i].f[j].s.f<<endl;
            cout<<"\t\tDistance: "<<solutions[i].f[j].s.s<<endl;
        }
        cout<<"\t Total Distance: "<<solutions[i].s<<endl;
    }
}
