#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 1e18
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
	cout<<mn<<endl;
	for(int x:res)
		cout<<x<<' ';
	cout<<endl;
	return make_pair(mn,res);
}
int main()
{
	int n,c;
	cout<<"Enter number of people and bus capacity:"<<endl;
	cin>>n>>c;
	vector<vector<ll>> adj(n,vector<ll>(n));
	vector<ll> fdist(n);
	cout<<"Enter the adjacency matrix:"<<endl;
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	{
		cin>>adj[i][j];
	}
	cout<<"Enter the destination distance vector"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>fdist[i];
	}
	vector<ll> x;
	cout<<"Enter length of sequence, followed by sequence"<<endl;
	int l;
	cin>>l;
	x.resize(l);
	for(int i=0;i<l;i++)	cin>>x[i];
	route(adj,fdist,x);
}