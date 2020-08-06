#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define ll long long
#define INF 1e18
fstream route_file;
pair<ll,vector<int>> route(vector<vector<ll>>& adj,vector<ll>& fdist,vector<ll>& x)
{
	int n=x.size();
	int MAX=(1<<n);
	vector<vector<ll>> dp(MAX,vector<ll>(n,INF));
	vector<vector<pair<int,int>>> backtrack(MAX,vector<pair<int,int>>(n));
	for(int i=0;i<n;i++)
		dp[0][i]=0;
	for(int mask=0;mask<MAX;mask++)
	{
		for(int i=0;i<n;i++)
		{
			if(dp[mask][i]==INF)	continue;
			for(int j=0;j<n;j++)
			{
				if(mask&(1<<j))	continue;
				int nmask=mask|(1<<j);
				ll cost=dp[mask][i]+adj[x[i]][x[j]];
				if(nmask==MAX-1)
					cost+=fdist[x[j]];
				if(cost<dp[nmask][j])
				{
					dp[nmask][j]=cost;
					backtrack[nmask][j]=make_pair(mask,i);
				}
			}
		}
	}
	ll mn=INF;
	int curr;
	for(int i=0;i<n;i++)
		if(mn>dp[MAX-1][i])
		{
			mn=dp[MAX-1][i];
			curr=i;
		}
	vector<int> res;
	int mask=MAX-1;
	while(mask>0)
	{
		res.push_back(x[curr]);
		pair<int,int> temp=backtrack[mask][curr];
		mask=temp.first;
		curr=temp.second;
	}
	//cout<<mn<<endl;
	vector<int>rev;
	for(int i=res.size()-1;i>=0;i--)
	{
		rev.push_back(res[i]);
	}
	for(int i:rev)
	{
		route_file<<i<<" ";
	}
	route_file<<endl;
	return make_pair(mn,res);
}
int main()
{
	int n,c;
	fstream graph;
	route_file.open("../route.txt");
	graph.open("graph.txt");
	graph>>n;

	vector<vector<ll>> adj(n,vector<ll>(n));
	vector<ll> fdist(n);
	
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	{
		graph>>adj[i][j];
	}
	fstream dest;
	dest.open("dest.txt");
	for(int i=0;i<n;i++)
	{
		dest>>fdist[i];
	}
	vector<ll> x;
	fstream bus;
	bus.open("CLUSTERS.txt");

	int l;
	bus>>l;
	int cl_size;
	ll tot=0;
	route_file<<l<<endl;
	for(int i=0;i<l;i++)
	{	
		
		bus>>cl_size;
		x.resize(cl_size);
		for(int j=0;j<cl_size;j++)
		{
			bus>>x[j];
		}
		route_file<<x.size()<<endl;
		int s=route(adj,fdist,x).first;
		cout<<"Bus "<<i+1<<" "<<s<<endl;
		tot+=s;
		
	}
	cout<<"Total distance is "<<tot<<endl;

}
